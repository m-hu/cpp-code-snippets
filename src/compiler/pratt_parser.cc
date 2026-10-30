#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <memory>
#include <stdexcept>

using namespace std;

enum class TokenType {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    CARET,
    LPAREN,
    RPAREN,
    END_OF_INPUT
};

struct Token {
    TokenType type;
    int value = 0;
};

class Lexer {
    string src;
    size_t pos = 0;
public:
    explicit Lexer(string s) : src(std::move(s)) {}

    Token next_token() {
        while (pos < src.size() && isspace(static_cast<unsigned char>(src[pos]))) {
            ++pos;
        }
        if (pos >= src.size()) {
            return {TokenType::END_OF_INPUT, 0};
        }
        char c = src[pos];
        if (isdigit(static_cast<unsigned char>(c))) {
            int val = 0;
            while (pos < src.size() && isdigit(static_cast<unsigned char>(src[pos]))) {
                val = val * 10 + (src[pos] - '0');
                ++pos;
            }
            return {TokenType::NUMBER, val};
        }
        ++pos;
        switch (c) {
            case '+': return {TokenType::PLUS, 0};
            case '-': return {TokenType::MINUS, 0};
            case '*': return {TokenType::STAR, 0};
            case '/': return {TokenType::SLASH, 0};
            case '^': return {TokenType::CARET, 0};
            case '(': return {TokenType::LPAREN, 0};
            case ')': return {TokenType::RPAREN, 0};
            default: return {TokenType::END_OF_INPUT, 0};
        }
    }
};

struct ASTNode {
    string op;
    int val = 0;
    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;

    string to_sexpr() const {
        if (op.empty()) {
            return to_string(val);
        }
        if (!right) {
            return "(" + op + " " + left->to_sexpr() + ")";
        }
        return "(" + op + " " + left->to_sexpr() + " " + right->to_sexpr() + ")";
    }

    long long eval() const {
        if (op.empty()) return val;
        if (!right) {
            if (op == "-") return -left->eval();
            return left->eval();
        }
        long long l = left->eval();
        long long r = right->eval();
        if (op == "+") return l + r;
        if (op == "-") return l - r;
        if (op == "*") return l * r;
        if (op == "/") return (r == 0) ? 0 : (l / r);
        if (op == "^") {
            long long res = 1;
            for (long long i = 0; i < r; ++i) res *= l;
            return res;
        }
        return 0;
    }
};

class PrattParser {
    Lexer lexer;
    Token curr;

    void advance() {
        curr = lexer.next_token();
    }

    pair<int, int> infix_binding_power(TokenType op) {
        switch (op) {
            case TokenType::PLUS:
            case TokenType::MINUS:
                return {10, 11}; // Left-associative
            case TokenType::STAR:
            case TokenType::SLASH:
                return {20, 21}; // Left-associative
            case TokenType::CARET:
                return {31, 30}; // Right-associative
            default:
                return {-1, -1};
        }
    }

public:
    explicit PrattParser(const string& s) : lexer(s) {
        advance();
    }

    shared_ptr<ASTNode> parse_expression(int min_bp = 0) {
        shared_ptr<ASTNode> lhs;

        // Prefix
        if (curr.type == TokenType::NUMBER) {
            auto node = make_shared<ASTNode>();
            node->val = curr.value;
            advance();
            lhs = node;
        } else if (curr.type == TokenType::MINUS) {
            advance();
            auto rhs = parse_expression(40); // High binding power for unary minus
            auto node = make_shared<ASTNode>();
            node->op = "-";
            node->left = rhs;
            lhs = node;
        } else if (curr.type == TokenType::LPAREN) {
            advance();
            lhs = parse_expression(0);
            if (curr.type == TokenType::RPAREN) {
                advance();
            }
        } else {
            return nullptr;
        }

        // Infix loop
        while (true) {
            auto bp = infix_binding_power(curr.type);
            int l_bp = bp.first;
            int r_bp = bp.second;
            if (l_bp < min_bp) {
                break;
            }

            string op_str;
            switch (curr.type) {
                case TokenType::PLUS: op_str = "+"; break;
                case TokenType::MINUS: op_str = "-"; break;
                case TokenType::STAR: op_str = "*"; break;
                case TokenType::SLASH: op_str = "/"; break;
                case TokenType::CARET: op_str = "^"; break;
                default: break;
            }
            advance();

            auto rhs = parse_expression(r_bp);
            auto node = make_shared<ASTNode>();
            node->op = op_str;
            node->left = lhs;
            node->right = rhs;
            lhs = node;
        }

        return lhs;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int num_exprs = 0;
    if (!(cin >> num_exprs)) return 0;
    string line;
    getline(cin, line); // consume newline

    for (int i = 0; i < num_exprs; ++i) {
        getline(cin, line);
        if (line.empty()) continue;
        PrattParser parser(line);
        auto ast = parser.parse_expression();
        if (ast) {
            cout << ast->to_sexpr() << " = " << ast->eval() << "\n";
        } else {
            cout << "PARSE_ERROR\n";
        }
    }

    return 0;
}
