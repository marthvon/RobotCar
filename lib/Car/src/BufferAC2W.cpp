#include "BufferAC2W.h"

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

BufferAC2W::Instruction::Instruction(const unsigned long p_delay, const COMMAND* const p_list, const uint8_t length, const float* const p_parameters)
    : delay(p_delay), list(p_list), cmd_length(length), parameters(p_parameters)
{}
BufferAC2W::Instruction::~Instruction() {
    delete[] list;
    delete[] parameters;
}
void BufferAC2W::addBuffer(Instruction* p_instruction) {
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
void BufferAC2W::buffer_reset(const unsigned long after_ms) {
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::RESET}, 1, nullptr));
}
void BufferAC2W::buffer_speed_angle(const unsigned long after_ms, const float speed, const float angle) {
    addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::SPEED, COMMAND::ANGLE}, 2, new float[2]{speed, angle}));
}
void BufferAC2W::buffer_speed(const unsigned long after_ms, const float speed, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::RESET, COMMAND::SPEED}, 2, new float(speed)));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::SPEED}, 1, new float(speed)));
}
void BufferAC2W::buffer_angle(const unsigned long after_ms, const float angle, const bool isReset) {
    if(isReset) {
        addBuffer(new Instruction(after_ms, new COMMAND[2]{COMMAND::RESET, COMMAND::ANGLE}, 2, new float(angle)));
        return;
    }
    addBuffer(new Instruction(after_ms, new COMMAND[1]{COMMAND::ANGLE}, 1, new float(angle)));
}

BufferAC2W::BufferAC2W(AnalogCar2W& p_car) : isOwned(false), car(&p_car) {}
BufferAC2W::BufferAC2W(AnalogCar2W&& p_car) : isOwned(true), car(new AnalogCar2W(p_car)) {}
BufferAC2W::BufferAC2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel) 
    : isOwned(true), car(new AnalogCar2W(p_forwardLeftWheel, p_backwardLeftWheel, p_forwardRightWheel, p_backwardRightWheel))
{}
BufferAC2W::~BufferAC2W() {
    if(isOwned)
        delete car;
    do {
        back = root->next;
        delete root;
    } while(root = back);
}
void BufferAC2W::begin() {
    if(car && isOwned)
        car->begin();
}
Car::AnalogCar2W* BufferAC2W::get_car() const {
    return car;
}

void BufferAC2W::run(const unsigned long delta) {
    if(!root)
        return;
    tick += delta;
    if(tick < root->delay)
        return;
    tick -= root->delay;
    const float* args = root->parameters; 
    for(const COMMAND* cmd = root->list; cmd != root->list + root->cmd_length; ++cmd) {
        switch (*cmd)
        {
        case COMMAND::RESET:
            car->reset(); break;
        case COMMAND::SPEED:
            car->setSpeed(*args); ++args; break;
        case COMMAND::ANGLE:
            car->setAngle(*args); ++args;
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
