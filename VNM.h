//
// Created by adama on 5/10/2017.
//

#ifndef SS_COMPILERC_VNM_H
#define SS_COMPILERC_VNM_H

#include <vector>

using namespace std;

typedef enum {RET = 0, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ} operationModifiers;

typedef enum {LIT = 0, } operationCodes;

//Instruction Class
class Instruction{
private:
    int opCode,
            lexicographicalLevel,
            modifier;
public:

    //Constructor/Destructor
    Instruction(int _opCode = 0, int _lexLevel = 0, int _modifier = 0)
    {
        Instruction::opCode = _opCode;
        Instruction::lexicographicalLevel = _lexLevel;
        Instruction::modifier = _modifier;
    };


    void setNewInstruction(int _opCode = 0, int _lexLevel = 0, int _modifier = 0);

    //Header Defined Functions - Mostly just some getters and setters.
    //Get the OpCode
    int getOpCode() const {
        return opCode;
    }

    //Get the Lexicographical Level
    int getLexicographicalLevel() const {
        return lexicographicalLevel;
    }

    //Get the Modifier Value
    int getModifier() const {
        return modifier;
    }

    //Set The OptCode
    void setOpCode(int opCode) {
        Instruction::opCode = opCode;
    }

    //Set the Lexicographical Level
    void setLexicographicalLevel(int lexicographicalLevel) {
        Instruction::lexicographicalLevel = lexicographicalLevel;
    }

    //Set the Modifer value
    void setModifier(int m) {
        Instruction::modifier = m;
    }
};

//Virtual Machine Instruction Queue
class VMQueue{
private:
    int InstructionRegisterIndex = 0, programCounter = 0;

    vector<Instruction> InstructionQueue;

    Instruction instructionRegister;



public:
    VMQueue();
    ~VMQueue();

    // Adds a Instruction to the end of the queue.
    void addInstruction(Instruction _instruction);

    // Gets an instruction from the beginning of the queue.
    void popInstruction(Instruction &_instructionRegister);

    // Return the top instruction of the stack.
    int getTop();

};

//Virtual machine Class
class VirtualMachine{

private:
    int maxStackHeight = 2000,
            maxCodeLength = 500,
            maxLexicographicalLevel = 3,
            stackPointer = -1,
            basePointer = 0,
            programCounter = 0;

    Instruction IRegister;
    VMQueue instructionQueue;
    vector<int> codeStack;

    // Return from the current procedure.
    void ret();

    // Set the top value on the stack to it's negative representation.
    void neg();

    /* Add the top two values on the stack and store it to the first value. the second value is discarded.
     * STACK [base][][][][stackPointer]
     * Decriment the stack pointer
     * STACK [base][][][stackPointer][stackPointer + 1]
     * Set the stack value at stackPointer to STACK[stackPointer] + STACK[StackPointer + 1]
     * Remove STACK[stackPointer + 1]
     *
     */
    void add();

    // Subtract the top two values of the stack is same manner as addition.
    void sub();

    //Multiply the two values at the top of the stack.
    void mult();

    // Divide the valuse at the top of the stack.
    void div();

    // If the value at the top of stack is odd, set it to 1, else 0.
    void odd();

    // Run mod operation on the top value of the stack in the same manner as addition.
    void mod();

    // Equal Comparison of the top value of the stack in the same manner as addition.
    void equal();

    // NotEqual Comparison of the top value of the stack in the same manner as addition.
    void notEqual();

    void lessThan();

    void lessThanEqualTo();

    void greaterThan();

    void greaterThanEqualTo();

    // Non Arithmetic Ops

    void load();

    void store();

    void call();

    void increment();

    void jump();

    void jumpConditional();

    void out();

    void in();

public:
    VirtualMachine(){
        VirtualMachine::IRegister.setNewInstruction();
    };

    ~VirtualMachine(){};

    int getBase(int _level, int _base);

    // Fetch the next instruction from the instruction queue and place it into the IR register.
    // Increment Program Counter by one.
    void fetch();

    // Execute the code in the instruction register.
    void execute();

    void operation();

};


#endif //SS_COMPILERC_VNM_H



