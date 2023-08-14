#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::vector<int> parseMove(std::string coordinate)
{
    std::vector<int> coordinate_values;
    
    int letter = (int) coordinate[0] - (int) 'a';
    int number = 7 - ((int) coordinate[1] - (int) '1');
    coordinate_values.push_back(number);
    coordinate_values.push_back(letter);

    return coordinate_values;
};

class Move
{
    public:

    std::vector<int> from_coords;
    std::vector<int> to_coords;

    Move(bool isString, std::string move_text="")
    {
        if (isString)
        {
        std::string move_1 = move_text.substr(0, 2);
        std::string move_2 = move_text.substr(3,4);
        from_coords = parseMove(move_1);
        to_coords = parseMove(move_2);
        };
    };

    void intIndexMove(int from_row, int from_collumn, int to_row, int to_collumn)
    {
        from_coords.push_back(from_row);
        from_coords.push_back(from_collumn);
        to_coords.push_back(to_row);
        to_coords.push_back(to_collumn);
    };
};

class Piece
{
    public:

    int pieceNumber;
    bool isWhite;
    bool isEmpty;
    std::string piece_symbol;
    bool hasMoved;

    void add_info(int pcNumber, bool amWhite, std::string symbol, bool amEmpty, bool moved = false)
    {
        pieceNumber = pcNumber;
        isWhite = amWhite;
        isEmpty = amEmpty;
        piece_symbol = symbol;
        hasMoved = moved;
    };

    void moved()
    {
        hasMoved = true;
    };

    void setEnP(bool amWhite)
    {
        pieceNumber = 6;
        isWhite = amWhite;
        isEmpty = true;
        piece_symbol = "  ";
        hasMoved = false;
    };
};

class Board
{
    public:
    Piece board[8][8];
    bool isWhite;
    bool whiteCastleQueenside;
    bool whiteCastleKingside;
    bool blackCastleQueenside;
    bool blackCastleKingside;
    bool enPassentAvailable;
    std::vector<int> enPassentCoords;

    std::string fen_format;

    std::vector<Move> getRookMoves(int row, int collumn, int isWhite)
    {

        std::vector<Move> rookMoves;

        // Rows Down
        for (int i = 1; row + i < 8; i++)
        {
            Piece check_piece = board[row + i][collumn];
            if ((check_piece.isEmpty || check_piece.isWhite != isWhite)) 
            {
                Move rookMove(false);
                rookMove.intIndexMove(row, collumn, row + i, collumn);
                rookMoves.push_back(rookMove);
            } else {
                break;
            };
        };

        // Rows Up

        for (int i = 1; row - i >= 0; i++)
        {
            Piece check_piece = board[row - i][collumn];
            if ((check_piece.isEmpty || check_piece.isWhite != isWhite)) 
            {
                Move rookMove(false, "");
                rookMove.intIndexMove(row, collumn, row - i, collumn);
                rookMoves.push_back(rookMove);
            } else {
                break;
            };
        };

        // Collumns Up
        for (int i = 1; collumn + i < 8; i++)
        {
            Piece check_piece = board[row][collumn + i];
            if ((check_piece.isEmpty || check_piece.isWhite != isWhite)) 
            {
                Move rookMove(false, "");
                rookMove.intIndexMove(row, collumn, row, collumn + i);
                rookMoves.push_back(rookMove);
            } else {
                break;
            };
        };

        // Collumns Down
        for (int i = 1; collumn - i >= 0; i++)
        {
            Piece check_piece = board[row][collumn - i];
            if ((check_piece.isEmpty || check_piece.isWhite != isWhite)) 
            {
                Move rookMove(false, "");
                rookMove.intIndexMove(row, collumn, row, collumn - i);
                rookMoves.push_back(rookMove);
            } else {
                break;
            };
        };

        return rookMoves;

    };

    std::vector<Move> getKnightMoves(int row, int collumn, bool isWhite)
    {

        std::vector<Move> knightMoves;

        if (collumn + 1 < 8)
        {   
            if (row + 2 < 8 && (board[row + 2][collumn + 1].isEmpty || board[row + 2][collumn + 1].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row + 2, collumn + 1);
                knightMoves.push_back(knightMove);
            };
            if (row - 2 >= 0 && (board[row - 2][collumn + 1].isEmpty || board[row - 2][collumn + 1].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row - 2, collumn + 1);
                knightMoves.push_back(knightMove);
            };
        }
        if (collumn - 1 >= 0)
        {   
            if (row + 2 < 8 && (board[row + 2][collumn - 1].isEmpty || board[row + 2][collumn - 1].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row + 2, collumn - 1);
                knightMoves.push_back(knightMove);
            };
            if (row - 2 >= 0 && (board[row - 2][collumn - 1].isEmpty || board[row - 2][collumn - 1].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row - 2, collumn - 1);
                knightMoves.push_back(knightMove);
            };
        };

        if (row + 1 < 8)
        {   
            if (collumn + 2 < 8 && (board[row + 1][collumn + 2].isEmpty || board[row + 1][collumn + 2].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row + 1, collumn + 2);
                knightMoves.push_back(knightMove);
            };
            if (collumn - 2 >= 0 && (board[row + 1][collumn - 2].isEmpty || board[row + 1][collumn - 2].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row + 1, collumn - 2);
                knightMoves.push_back(knightMove);
            };
        }
        if (row - 1 >= 0)
        {   
            if (collumn + 2 < 8 && (board[row - 1][collumn + 2].isEmpty || board[row - 1][collumn + 2].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row - 1, collumn + 2);
                knightMoves.push_back(knightMove);
            };
            if (collumn - 2 >= 0 && (board[row - 1][collumn - 2].isEmpty || board[row - 1][collumn - 2].isWhite != isWhite))
            {
                Move knightMove(false);
                knightMove.intIndexMove(row, collumn, row - 1, collumn - 2);
                knightMoves.push_back(knightMove);
            };
        };

        return knightMoves;
    };

    std::vector<Move> getBishopMoves(int row, int collumn, bool isWhite)
    {

        std::vector<Move> bishopMoves;

        // Up Right

        int i = 1;
        while (row - i >= 0 && collumn + i < 8)
        {
            Piece check_piece = board[row - i][collumn + i];
            if (!(check_piece.isEmpty))
            {
                if (check_piece.isWhite != isWhite)
                {
                    Move bishopMove(false);
                    bishopMove.intIndexMove(row, collumn, row - i, collumn + i);
                    bishopMoves.push_back(bishopMove);
                };
                break;

            } else {
                Move bishopMove(false);
                bishopMove.intIndexMove(row, collumn, row - i, collumn + i);
                bishopMoves.push_back(bishopMove);
            }   
        };

        // Down Right

        i = 1;
        while (row + i < 8 && collumn + i < 8)
        {
            Piece check_piece = board[row + i][collumn + i];
            if (!(check_piece.isEmpty))
            {
                if (check_piece.isWhite != isWhite)
                {
                    Move bishopMove(false);
                    bishopMove.intIndexMove(row, collumn, row + i, collumn + i);
                    bishopMoves.push_back(bishopMove);
                };
                break;

            } else {
                Move bishopMove(false);
                bishopMove.intIndexMove(row, collumn, row + i, collumn + i);
                bishopMoves.push_back(bishopMove);
            }   
        };

        // Up Left

        i = 1;
        while (row - i >= 0 && collumn - i >= 0)
        {
            Piece check_piece = board[row - i][collumn - i];
            if (!(check_piece.isEmpty))
            {
                if (check_piece.isWhite != isWhite)
                {
                    Move bishopMove(false);
                    bishopMove.intIndexMove(row, collumn, row - i, collumn - i);
                    bishopMoves.push_back(bishopMove);
                };
                break;

            } else {
                Move bishopMove(false);
                bishopMove.intIndexMove(row, collumn, row - i, collumn - i);
                bishopMoves.push_back(bishopMove);
            }   
        };

        // Down Left

        i = 1;
        while (row + i < 8 && collumn - i >= 0)
        {
            Piece check_piece = board[row + i][collumn - i];
            if (!(check_piece.isEmpty))
            {
                if (check_piece.isWhite != isWhite)
                {
                    Move bishopMove(false);
                    bishopMove.intIndexMove(row, collumn, row + i, collumn - i);
                    bishopMoves.push_back(bishopMove);
                };
                break;

            } else {
                Move bishopMove(false);
                bishopMove.intIndexMove(row, collumn, row + i, collumn - i);
                bishopMoves.push_back(bishopMove);
            }   
        };

        return bishopMoves;

    };

    bool inBoardRange(int row, int collumn)
    {
        if (row < 0 || row > 7)
        {
            return false;
        };
        if (collumn < 0 || collumn > 7)
        {
            return false;
        };
        return true;
    };

    std::vector<Move> getKingMoves(int row, int collumn, bool isWhite)
    {
        std::vector<Move> kingMoves;

        for (int new_row = row - 1; new_row <= row + 1; new_row++)
        {
            if (inBoardRange(new_row, collumn + 1))
            {
                Piece check_piece = board[new_row][collumn + 1];
                if (!(check_piece.isEmpty))
                {
                    if (check_piece.isWhite != isWhite)
                    {
                        Move kingMove(false);
                        kingMove.intIndexMove(row, collumn, new_row, collumn + 1);
                        kingMoves.push_back(kingMove);
                    }
                    break;
                };
                Move kingMove(false);
                kingMove.intIndexMove(row, collumn, new_row, collumn + 1);
                kingMoves.push_back(kingMove);
            };
        };

        for (int new_row = row - 1; new_row <= row + 1; new_row++)
        {
            if (inBoardRange(new_row, collumn - 1))
            {
                Piece check_piece = board[new_row][collumn - 1];
                if (!(check_piece.isEmpty))
                {
                    if (check_piece.isWhite != isWhite)
                    {
                        Move kingMove(false);
                        kingMove.intIndexMove(row, collumn, new_row, collumn - 1);
                        kingMoves.push_back(kingMove);
                    }
                    break;
                };
                Move kingMove(false);
                kingMove.intIndexMove(row, collumn, new_row, collumn - 1);
                kingMoves.push_back(kingMove);
            };
        };

        if (collumn - 1 >= 0)
        {
            Piece check_piece = board[row][collumn - 1];
            if (check_piece.isEmpty || check_piece.isWhite != isWhite)
            {
            Move kingMove(false);
            kingMove.intIndexMove(row, collumn, row, collumn - 1);
            kingMoves.push_back(kingMove);
            }
        };

        if (collumn + 1 < 8)
        {
            Piece check_piece = board[row][collumn + 1];
            if (check_piece.isEmpty || check_piece.isWhite != isWhite)
            {
            Move kingMove(false);
            kingMove.intIndexMove(row, collumn, row, collumn + 1);
            kingMoves.push_back(kingMove);
            };
        };

    return kingMoves;

    };

    std::vector<Move> getPawnMoves(int row, int collumn, bool isWhite)
    {
        std::vector<Move> pawnMoves;
        int direction;
        switch (isWhite) {case true: direction *= -1; break; case false: break;};
    };

    std::vector<Move> getLegalMoves(bool isWhite)
    {
        std::vector<Move> final_moves;
        for (int i = 0; i < 8; i++)
        {
            int j = 0;

            std::vector<Move> moves;
            for (Piece piece : board[i])
            {
                j++;
                if (!(piece.isEmpty))
                {
                    std::vector<Move> pieceMoves;
                    std::vector<Move> queenMovesONE;
                    std::vector<Move> queenMovesTWO;
                    if (piece.isWhite == isWhite)
                    {
                        switch (piece.pieceNumber)
                        {
                            case 1:
                                pieceMoves = getRookMoves(i, j, isWhite);
                                break;
                            case 2:
                                pieceMoves = getKnightMoves(i, j, isWhite);
                                break;
                            case 3:
                                pieceMoves = getBishopMoves(i, j, isWhite);
                                break;
                            case 4:
                                queenMovesONE = getRookMoves(i, j, isWhite);
                                queenMovesTWO = getBishopMoves(i, j, isWhite);
                                for (Move move : queenMovesONE)
                                {
                                    pieceMoves.push_back(move);
                                };
                                for (Move move : queenMovesTWO)
                                {
                                    pieceMoves.push_back(move);
                                };
                            case 5:
                                pieceMoves = getKingMoves(i, j, isWhite);
                                break;
                        }
                    } else {
                        std::cout << "Nah";
                    };
                };
            };
        };
    };

    void printStats()
    {
        std::cout << isWhite << std::endl << whiteCastleQueenside << std::endl;
        std::cout << whiteCastleKingside << std::endl << blackCastleKingside << std::endl;
        std::cout << blackCastleQueenside << std::endl << enPassentAvailable << std::endl;
        std::cout << enPassentCoords[0] << std::endl << enPassentCoords[1] << std::endl;        
    };

    std::string getFen(std::string path)
    {
        std::string line;
        std::ifstream file(path);
        if (file.is_open())
        {
            std::getline(file, line);
            file.close();
        };
        return line;
    };

    std::vector<int> parseGenericCoords(char let, char num)
    {
        std::vector<int> coords;
        int letter = let;
        int number = num;

        coords.push_back(letter - 97);
        coords.push_back(number - 49);

        return coords;
    };

    void drawBoard()
    {

        std::string bg_color_1 = "\033[1;40m";
        std::string bg_color_2 = "\033[1;47m";
        int color_tracker = 0;
        std::string bg_color;

        for (int rows = 0; rows < 8; rows++)
        {
            for (int collumns = 0; collumns < 8; collumns++)
            {
                if (color_tracker % 2)
                {
                    bg_color = bg_color_1;
                } else {
                    bg_color = bg_color_2;
                };
                std::cout << bg_color << board[rows][collumns].piece_symbol;
                color_tracker++;
            };
            std::cout << "\033[1;40m"<< std::endl;
            color_tracker++;
        };
    };

    void makeBoard(std::string path = "./positions/starting_position.txt")
    {
        fen_format = getFen(path);
        int i = 0;
        char separator = ' ';
        std::string position;
        while (fen_format[i] != separator)
        {
            position += fen_format[i];
            i++;
        };
        i++;
        if (fen_format[i] == 'w')
        {
            isWhite = true;
        } else {
            isWhite = false;
        };
        i += 2;
        while (fen_format[i] != separator)
        {
            if (fen_format[i] == 'K')
            {
                whiteCastleKingside = true;
            };
            if (fen_format[i] == 'Q')
            {
                whiteCastleQueenside = true;
            };
            if (fen_format[i] == 'k')
            {
                blackCastleKingside = true;
            };
            if (fen_format[i] == 'q')
            {
                blackCastleQueenside = true;
            };
            i++;
        };
        i++;
        if (fen_format[i] != '-')
        {
            enPassentCoords = parseGenericCoords(fen_format[i], fen_format[i + 1]);
            enPassentAvailable = true;
        } else {
            enPassentAvailable = false;
        };

        int collumn = 0;
        int row = 0;

        for (char character : position)
        {

            collumn = collumn % 8;

            bool emptySquares = false;
            int piece_no = 0;
            bool isPieceWhite;
            std::string symbol;

            if (character == '/')
            {
                row += 1;
                collumn = 0;
                emptySquares = true;
            } else if (character == 'r')
            {
                piece_no = 1;
                isPieceWhite = false;
                symbol = "\033[1;31mR ";
            } else if (character == 'R')
            {
                symbol = "\033[1;35mR ";
                piece_no = 1;
                isPieceWhite = true;
            } else if (character == 'n')
            {
                symbol = "\033[1;31mN ";
                piece_no = 2;
                isPieceWhite = false;
            } else if (character == 'N')
            {
                symbol = "\033[1;35mN ";
                piece_no = 2;
                isPieceWhite = true;
            } else if (character == 'b')
            {
                symbol = "\033[1;31mB ";
                piece_no = 3;
                isPieceWhite = false;
            } else if (character == 'B')
            {
                symbol = "\033[1;35mB ";
                piece_no = 3;
                isPieceWhite = true;
            } else if (character == 'q')
            {
                symbol = "\033[1;31mQ ";
                piece_no = 4;
                isPieceWhite = false;
            } else if (character == 'Q')
            {
                symbol = "\033[1;35mQ ";
                piece_no = 4;
                isPieceWhite = true;
            } else if (character == 'k')
            {
                symbol = "\033[1;31mK ";
                piece_no = 5;
                isPieceWhite = false;
            } else if (character == 'K')
            {
                symbol = "\033[1;35mK ";
                piece_no = 5;
                isPieceWhite = true;
            } else if (character == 'p')
            {
                symbol = "\033[1;31mP ";
                piece_no = 6;
                isPieceWhite = false;
            } else if (character == 'P')
            {
                symbol = "\033[1;35mP ";
                piece_no = 6;
                isPieceWhite = true;
            }
            else {
                int charToInt = character;
                int range = charToInt - 48;
                for (int i = 0; i < range; i++)
                {
                    Piece new_piece;
                    new_piece.add_info(0, true, "\033[1;32m  ", true);
                    board[row][collumn] = new_piece;
                    collumn += 1;
                };
                emptySquares = true;
            };
            if (!emptySquares)
            {
            Piece new_piece;
            new_piece.add_info(piece_no, isPieceWhite, symbol, true);
            board[row][collumn] = new_piece;               
            collumn += 1;
            };
        };
    };
    void doMove(Move curr_move)
    {
        std::vector<int> from = curr_move.from_coords;
        std::vector<int> to = curr_move.to_coords;

        Piece empty_piece;
        empty_piece.add_info(0, true, "  ", true);

        board[to[0]][to[1]] = board[from[0]][from[1]];
        board[from[0]][from[1]] = empty_piece;

    };
};

bool isInputFormatCorrect(std::string input)
{

    if (!(input.length() == 5))
    {
        return false;
    };

    int divider = input[2];

    int l_checked = 0;
    while (l_checked <= 3)
    {
        int l_value = input[l_checked];
        if (!((l_value >= (int) 'a' && l_value <= (int) 'h') || (l_value >= (int) 'A' && l_value <= (int) 'H')))
        {
            return false;
        };
        l_checked += 3;
    };

    int n_checked = 1;
    while (n_checked <= 4)
    {
        int n_value = input[n_checked];

        if (!(((int) n_value >= (int) '1' ) && ((int) n_value <= (int) '8')))
        {
            return false;
        };
        n_checked += 3;
    };
    if (!(divider == '-' || divider == 'x'))
    {
        return false;
    };

    return true;
};

int start_offline_game()
{
    Board board;
    board.makeBoard();
    board.drawBoard();

    while (true)
    {
        std::string input;
        std::cin >> input;
        if (isInputFormatCorrect(input))
        {
            Move newMove(true, input);
            board.doMove(newMove);
            board.drawBoard();

        } else {
            std::cout << "Nar!";
        };
    };
    return 0;
};

int main()
{
    start_offline_game();
    return 0;
};