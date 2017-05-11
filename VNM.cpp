//
// Created by adama on 5/10/2017.
//

#include "VNM.h"

void Instruction::setNewInstruction(int _opCode, int _lexLevel, int _modifier) {

    Instruction::opCode = _opCode;
    Instruction::lexicographicalLevel = _lexLevel;
    Instruction::modifier = _modifier;

}

// Stack size should never be more than 500, so we do not need to worry about a casting error.
int VMQueue::getTop() {
    return int(InstructionQueue.size());
}

void VMQueue::addInstruction(Instruction _instruction) {
    InstructionQueue.push_back(_instruction);           // Add a new instruction to the end of the instruction queue.
}

void VMQueue::popInstruction(Instruction &_instructionRegister) {
    _instructionRegister = InstructionQueue.front();    // Set the instruction register to the same
                                                        // value as the instruction at the start of the queue.
    // Do not have to actually remove these.
    //InstructionQueue.erase(InstructionQueue.begin());   // Remove the first instruction from the queue.

}

// Get variables some number of levels l, in the activation record.
int VirtualMachine::getBase(int _level, int _base) {
    int b1 = _base;
    while(_level > 0)
    {
        b1 = codeStack.at(b1);
        _level--;
    }

    return 0;
}

void VirtualMachine::fetch() {
    // Fetch the instruction from the instruction queue and save it to the instruction register,
    instructionQueue.popInstruction(IRegister);
    // Increment the program counter to fetch next instruction.
    VirtualMachine::programCounter++;
}

void VirtualMachine::operation() {
    switch(IRegister.getModifier())
    {
        case RET: VirtualMachine::ret();
        case NEG: VirtualMachine::neg();
        case ADD: VirtualMachine::add();
        case SUB: VirtualMachine::sub();
        case MUL: VirtualMachine::mult();
        case DIV: VirtualMachine::div();
        case ODD: VirtualMachine::odd();
        case MOD: VirtualMachine::mod();
        case EQL: VirtualMachine::equal();
        case NEQ: VirtualMachine::notEqual();
        case LSS: VirtualMachine::lessThan();
        case LEQ: VirtualMachine::lessThanEqualTo();
        case GTR: VirtualMachine::greaterThan();
        case GEQ: VirtualMachine::greaterThanEqualTo();

    }
}

void VirtualMachine::execute() {
    switch(IRegister.getOpCode())
    {
        case LIT: operation();
    }
}

//Return from a function call.
void VirtualMachine::ret() {
    stackPointer = basePointer - 1;
    programCounter = codeStack.at(stackPointer + 3);
    basePointer = codeStack.at(stackPointer + 2);
}

// Set the value at the top of the stack to a negative.
void VirtualMachine::neg() {
    int temp = codeStack.at(stackPointer);
    codeStack.assign(stackPointer, temp);
}

// Add the top value on the stack to the value below it and save it at stackpointer - 1
void VirtualMachine::add() {
    stackPointer--;
    int temp = codeStack.at(stackPointer);

    codeStack.assign(stackPointer, codeStack.at(stackPointer + 1) + temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

// Subtract top value of the stack from the value below it and store it
// in the stack position below it.
void VirtualMachine::sub() {
    stackPointer--;
    int temp = codeStack.at(stackPointer);

    codeStack.assign(stackPointer, codeStack.at(stackPointer + 1) - temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}


void VirtualMachine::mult() {
    stackPointer--;
    int temp = codeStack.at(stackPointer);

    codeStack.assign(stackPointer, codeStack.at(stackPointer + 1) * temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::div() {
    stackPointer--;
    int temp = codeStack.at(stackPointer);

    codeStack.assign(stackPointer, codeStack.at(stackPointer + 1) / temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::odd() {
    int temp = codeStack.at(stackPointer)%2;

    codeStack.assign(stackPointer, temp);
}

void VirtualMachine::mod() {
    stackPointer--;
    int temp = codeStack.at(stackPointer);

    codeStack.assign(stackPointer, codeStack.at(stackPointer + 1) % temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::equal() {
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer)== codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::notEqual(){
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer)!= codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::lessThan() {
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer)< codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::lessThanEqualTo() {
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer) <= codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}
void VirtualMachine::greaterThan(){
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer) > codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::greaterThanEqualTo() {
    stackPointer--;
    int temp = 0;

    if(codeStack.at(stackPointer) >= codeStack.at(stackPointer + 1))
        temp = 1;
    codeStack.assign(stackPointer, temp);
    codeStack.erase(codeStack.begin() + stackPointer);
}

void VirtualMachine::load() {
    stackPointer++;
    int temp = codeStack.at(getBase(IRegister.getLexicographicalLevel(), basePointer) + IRegister.getModifier());
    codeStack.assign(stackPointer,temp);

}

