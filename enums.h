#ifndef ENUMS_H
#define ENUMS_H

enum position{
    UPPER,
    CENTER,
    LOWER
};

enum boardStates{
    READY = 0,
    WAITING = 1,
    LOCKED = 2,
    SECURE = 3
};

enum players{
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5
};

enum highlights{
    NONE = 0,
    ACTIVE = 1,
    SPECIAL = 2,
    HOVER = 3,
    TEXT = 4
};

enum messageIDs{
    MOVED,
    TURN_ENDED,
    RESET_STATE,
    DEFEND,
    NO_FIELDS,
    SPAWN_RESOLVED
};

enum messageResponses{
    PASS,
    TRUE,
    FALSE,
};

enum pieceIDs{
    SWORD,
    SPEAR,
    SHIELD,
    BANNER,
    EYE,
    CROWN,
    PIECE_COUNT
};




#endif // ENUMS_H
