#include <iostream>
#include <memory>
#include <cmath>

enum class Color { White, Black };

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool isValid() const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
};

class Piece {
public:
    Color color;
    Position position;

    Piece(Color color, Position position) : color(color), position(position) {}
    virtual ~Piece() {}

    virtual bool canMove(const Position& newPosition) const = 0;
    virtual void move(const Position& newPosition) {
        if (canMove(newPosition)) {
            position = newPosition;
        } else {
            std::cout << "Invalid move!" << std::endl;
        }
    }

    virtual void print() const = 0;
};

class King : public Piece {
public:
    King(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        int dx = std::abs(position.x - newPosition.x);
        int dy = std::abs(position.y - newPosition.y);
        return (dx <= 1 && dy <= 1);
    }

    void print() const override {
        std::cout << (color == Color::White ? "K" : "k") << " ";
    }
};

class Queen : public Piece {
public:
    Queen(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        int dx = std::abs(position.x - newPosition.x);
        int dy = std::abs(position.y - newPosition.y);
        return (dx == dy || position.x == newPosition.x || position.y == newPosition.y);
    }

    void print() const override {
        std::cout << (color == Color::White ? "Q" : "q") << " ";
    }
};

class Rook : public Piece {
public:
    Rook(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        return (position.x == newPosition.x || position.y == newPosition.y);
    }

    void print() const override {
        std::cout << (color == Color::White ? "R" : "r") << " ";
    }
};

class Bishop : public Piece {
public:
    Bishop(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        int dx = std::abs(position.x - newPosition.x);
        int dy = std::abs(position.y - newPosition.y);
        return (dx == dy);
    }

    void print() const override {
        std::cout << (color == Color::White ? "B" : "b") << " ";
    }
};

class Knight : public Piece {
public:
    Knight(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        int dx = std::abs(position.x - newPosition.x);
        int dy = std::abs(position.y - newPosition.y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    void print() const override {
        std::cout << (color == Color::White ? "N" : "n") << " ";
    }
};

class Pawn : public Piece {
public:
    Pawn(Color color, Position position) : Piece(color, position) {}

    bool canMove(const Position& newPosition) const override {
        int dx = std::abs(position.x - newPosition.x);
        int dy = std::abs(position.y - newPosition.y);
        if (color == Color::White) {
            return (dy == 1 && dx == 0);  // White moves one step forward
        } else {
            return (dy == 1 && dx == 0);  // Black moves one step forward
        }
    }

    void print() const override {
        std::cout << (color == Color::White ? "P" : "p") << " ";
    }
};

class Board {
private:
    std::unique_ptr<Piece> board[8][8];

public:
    Board() {
        // Initialize board with pieces
        for (int i = 0; i < 8; ++i) {
            board[1][i] = std::make_unique<Pawn>(Color::White, Position(i, 1));
            board[6][i] = std::make_unique<Pawn>(Color::Black, Position(i, 6));
        }

        board[0][0] = std::make_unique<Rook>(Color::White, Position(0, 0));
        board[0][7] = std::make_unique<Rook>(Color::White, Position(7, 0));
        board[7][0] = std::make_unique<Rook>(Color::Black, Position(0, 7));
        board[7][7] = std::make_unique<Rook>(Color::Black, Position(7, 7));

        board[0][1] = std::make_unique<Knight>(Color::White, Position(1, 0));
        board[0][6] = std::make_unique<Knight>(Color::White, Position(6, 0));
        board[7][1] = std::make_unique<Knight>(Color::Black, Position(1, 7));
        board[7][6] = std::make_unique<Knight>(Color::Black, Position(6, 7));

        board[0][2] = std::make_unique<Bishop>(Color::White, Position(2, 0));
        board[0][5] = std::make_unique<Bishop>(Color::White, Position(5, 0));
        board[7][2] = std::make_unique<Bishop>(Color::Black, Position(2, 7));
        board[7][5] = std::make_unique<Bishop>(Color::Black, Position(5, 7));

        board[0][3] = std::make_unique<Queen>(Color::White, Position(3, 0));
        board[7][3] = std::make_unique<Queen>(Color::Black, Position(3, 7));

        board[0][4] = std::make_unique<King>(Color::White, Position(4, 0));
        board[7][4] = std::make_unique<King>(Color::Black, Position(4, 7));
    }

    void printBoard() const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j]) {
                    board[i][j]->print();
                } else {
                    std::cout << ". ";
                }
            }
            std::cout << std::endl;
        }
    }

    bool movePiece(Position from, Position to) {
        if (from.isValid() && to.isValid() && board[from.x][from.y]) {
            Piece* piece = board[from.x][from.y].get();
            if (piece->canMove(to)) {
                board[to.x][to.y] = std::move(board[from.x][from.y]);
                board[from.x][from.y] = nullptr;
                return true;
            }
        }
        return false;
    }
};

class Game {
private:
    Board board;
    Color currentPlayer;

public:
    Game() : currentPlayer(Color::White) {}

    void play() {
        while (true) {
            board.printBoard();
            std::cout << "Player " << (currentPlayer == Color::White ? "White" : "Black") << "'s turn.\n";

            // Example: Move piece (e.g., from (1, 1) to (2, 2))
            Position from(1, 1), to(2, 2);
            if (board.movePiece(from, to)) {
                currentPlayer = (currentPlayer == Color::White) ? Color::Black : Color::White;
            } else {
                std::cout << "Invalid move! Try again.\n";
            }
        }
    }
};

int main() {
    Game game;
    game.play();  // Start the game
    return 0;
}
