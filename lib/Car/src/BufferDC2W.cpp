#include "BufferDC2W.h"

#ifdef ASYNC
#define ASYNC_LOCK while(async_protection); ++async_protection
#else
#define ASYNC_LOCK
#endif

#ifdef ASYNC
#define ASYNC_UNLOCK --async_protection
#else
#define ASYNC_UNLOCK
#endif

using namespace Car::Buffer;

BufferDC2W::Instruction::Instruction(const unsigned long p_delay, const COMMAND* const p_list, const uint8_t length, const int* const p_parameters)
    : delay(p_delay), list(p_list), cmd_length(length), parameters(p_parameters)
{}
BufferDC2W::Instruction::~Instruction() {
    delete[] list;
    delete[] parameters;
}
void BufferDC2W::addBuffer(Instruction* p_instruction) {
    ASYNC_LOCK;
    if(!root) {
        root = p_instruction;
        back = root;
        ASYNC_UNLOCK;
        return;
    }
    back->next = p_instruction;
    back = p_instruction;
    ASYNC_UNLOCK;
}
void BufferDC2W::buffer_reset(const unsigned long after_ms) {
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::RESET}, 1, nullptr));
}
void BufferDC2W::buffer_go(const unsigned long after_ms, const bool go, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::RESET, COMMAND::GO}, 2, new int(go)));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::GO}, 1, new int(go)));
}
void BufferDC2W::buffer_reverse(const unsigned long after_ms, const bool reverse, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::RESET, COMMAND::REVERSE}, 2, new int(reverse)));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::REVERSE}, 1, new int(reverse)));
}
void BufferDC2W::buffer_stir(const unsigned long after_ms, const Car::STIR stir, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::RESET, COMMAND::STIR}, 2, new int((int)stir)));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::STIR}, 1, new int((int)stir)));
}
void BufferDC2W::buffer_go_reverse(const unsigned long after_ms,const bool go, const bool reverse, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[3]{COMMAND::RESET, COMMAND::GO, COMMAND::REVERSE}, 3, new int[2]{go, reverse}));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::GO, COMMAND::REVERSE}, 2, new int[2]{go, reverse}));
}
void BufferDC2W::buffer_go_stir(const unsigned long after_ms, const bool go, const Car::STIR stir, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[3]{COMMAND::RESET, COMMAND::GO, COMMAND::STIR}, 3, new int[2]{go, (int)stir}));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::GO, COMMAND::STIR}, 2, new int[2]{go, (int)stir}));
}
void BufferDC2W::buffer_reverse_stir(const unsigned long after_ms, const bool reverse, const Car::STIR stir, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[3]{COMMAND::RESET, COMMAND::REVERSE, COMMAND::STIR}, 3, new int[2]{reverse, (int)stir}));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::REVERSE, COMMAND::STIR}, 2, new int[2]{reverse, (int)stir}));
}
void BufferDC2W::buffer_go_reverse_stir(const unsigned long after_ms, const bool go, const bool reverse, const Car::STIR stir) {
    addBuffer(new Instruction(after_ms, new COMMAND[3]{COMMAND::GO, COMMAND::REVERSE, COMMAND::STIR}, 3, new int[3]{go, reverse, (int)(stir)}));
}


BufferDC2W::BufferDC2W(DigitalCar2W& p_car) : isOwned(false), car(&p_car) {}
BufferDC2W::BufferDC2W(DigitalCar2W&& p_car) : isOwned(true), car(new DigitalCar2W(p_car)) {}
BufferDC2W::BufferDC2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel) 
    : isOwned(true), car(new DigitalCar2W(p_forwardLeftWheel, p_backwardLeftWheel, p_forwardRightWheel, p_backwardRightWheel))
{}
BufferDC2W::~BufferDC2W() {
    if(isOwned)
        delete car;
    do {
        back = root->next;
        delete root;
    } while(root = back);
}
Car::DigitalCar2W* BufferDC2W::get_car() const {
    return car;
}
void BufferDC2W::begin() {
    if(car && isOwned)
        car->begin();
}

void BufferDC2W::run(const unsigned long delta) {
    if(!root)
        return;
    tick += delta;
    if(tick < root->delay)
        return;
    tick -= root->delay;
    const int* args = root->parameters; 
    for(const COMMAND* cmd = root->list; cmd != root->list + root->cmd_length; ++cmd) {
        switch (*cmd)
        {
        case COMMAND::RESET:
            car->reset(); break;
        case COMMAND::GO:
            car->setGo((bool)(*args)); ++args; break;
        case COMMAND::REVERSE:
            car->setReverse((bool)(*args)); ++args; break;
        case COMMAND::STIR:
            car->setStir((STIR)(*args)); ++args;
        }
    }
    Instruction* temp = root;
    ASYNC_LOCK;
    root = root->next;
    if(!root)
        back = nullptr;
    delete temp;
    ASYNC_UNLOCK;
}