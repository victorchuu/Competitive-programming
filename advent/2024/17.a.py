from dataclasses import dataclass, field
import re

def parse_input(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    # Initialize variables
    A = B = C = 0
    program = []

    # Regular expressions to match the register lines and program line
    register_pattern = re.compile(r'Register (\w): (\d+)')
    program_pattern = re.compile(r'Program: (.+)')

    for line in lines:
        # Match register lines
        register_match = register_pattern.match(line.strip())
        if register_match:
            register, value = register_match.groups()
            if register == 'A':
                A = int(value)
            elif register == 'B':
                B = int(value)
            elif register == 'C':
                C = int(value)
        
        # Match program line
        program_match = program_pattern.match(line.strip())
        if program_match:
            program = list(map(int, program_match.group(1).split(',')))

    return A, B, C, program

@dataclass
class Processor:
    A: int
    B: int
    C: int
    output: list[int] = field(default_factory=list)

    def combo(self, operand: int):
        if operand == 4:
            return self.A
        elif operand == 5:
            return self.B
        elif operand == 6:
            return self.C
        else:
            return operand

    def adv(self, operand: int, pointer: int):
        self.A = self.A // (2 ** self.combo(operand))
        return pointer + 2

    def bxl(self, operand: int, pointer: int):
        self.B ^= operand
        return pointer + 2

    def bst(self, operand: int, pointer: int):
        self.B = self.combo(operand) % 8
        return pointer + 2

    def jnz(self, operand: int, pointer: int):
        if self.A != 0:
            return operand
        return pointer + 2
    
    def bxc(self, operand: int, pointer: int):
        self.B ^= self.C
        return pointer + 2
    
    def out(self, operand: int, pointer: int):
        self.output.append(self.combo(operand) % 8)
        return pointer + 2
    
    def bdv(self, operand: int, pointer: int):
        self.B = self.A // (2 ** self.combo(operand))
        return pointer + 2
    
    def cdv(self, operand: int, pointer: int):
        self.C = self.A // (2 ** self.combo(operand))
        return pointer + 2
    

    def operate(self, opcode: int, operand: int, pointer: int):
        if opcode == 0:
            return self.adv(operand, pointer)
        elif opcode == 1:
            return self.bxl(operand, pointer)
        elif opcode == 2:
            return self.bst(operand, pointer)
        elif opcode == 3:
            return self.jnz(operand, pointer)
        elif opcode == 4:
            return self.bxc(operand, pointer)
        elif opcode == 5:
            return self.out(operand, pointer)
        elif opcode == 6:
            return self.bdv(operand, pointer)
        elif opcode == 7:
            return self.cdv(operand, pointer)

A, B, C, program = parse_input('input.txt')
processor = Processor(A,B,C)

i = 0
while i < len(program):
    opcode = program[i]
    if i+1 >= len(program):
        print("ERROR ERROR ERROR")
    operand = program[i+1]
    i = processor.operate(opcode, operand, i)


print(f"Register A: {processor.A}")
print(f"Register B: {processor.B}")
print(f"Register C: {processor.C}")
print(f"Output: {','.join([str(x) for x in processor.output])}")
