#ifndef ENUMS_H
#define ENUMS_H

enum position{
    UPPER,
    CENTER,
    LOWER
};

enum state{
    READY,
    WAITING
};

enum players{
    A = 0,
    B = 1
};

enum highlights{
    NONE = 0,
    ACTIVE = 1,
    SPECIAL = 2,
    HOVER = SPECIAL+1,
    TEXT
};

enum messageIDs{
    MOVED,
    TURN_ENDED,
    RESET_STATE,
    DEFEND,
    NO_FIELDS
};

enum messageResponses{
    PASS,
    TRUE,
    FALSE,
};


#endif // ENUMS_H
