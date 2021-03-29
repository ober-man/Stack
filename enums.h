#pragma once
enum Errors
{
    ALL_GOOD    = 0,
    ERR_CAP     = 1,
    ERR_SIZE    = 2,
    OVER_FLOW   = 3,
    EMPTY       = 4,
    ERR_CANARY  = 5,
    ERR_HASH    = 6,
    NO_MEM_MORE = 7,
    ERR_PTR     = 8
};

enum ConsoleColor
{
    Black         = 0,
    Blue          = 1,
    Green         = 2,
    Cyan          = 3,
    Red           = 4,
    Magenta       = 5,
    Brown         = 6,
    LightGray     = 7,
    DarkGray      = 8,
    LightBlue     = 9,
    LightGreen    = 10,
    LightCyan     = 11,
    LightRed      = 12,
    LightMagenta  = 13,
    Yellow        = 14,
    White         = 15
};

enum Cmd
{
    CREATE_ = 0,
    PUSH_ = 1,
    POP_BEFORE_ = 2,
    POP_AFTER_ = 3,
    TOP_ = 4,
    CLEAR_ = 5,
    SIZE_ = 6,
    PRINT_ = 7,
    DUMP_ = 8
};
