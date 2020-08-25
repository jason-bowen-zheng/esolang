from os.path import isfile
from sys import argv

def main():
    if len(argv) != 2:
        print('BrainFuck: except 2 arguments, found %d' % len(argv))
    else:
        if argv[1] == '--help':
            print('BrainFuck v1.0\n')
            print('+\tptr+=1')
            print('-\tptr-=1')
            print('>\t*ptr+=1')
            print('<\t*ptr-=1')
            print('.\tprint(*ptr)')
            print(',\t*ptr=input()')
            print('[\twhile(*ptr)')
            print(']\tend while')
        elif argv[1] == '--version':
            print('BrainFuck v1.0')
        else:
            run(argv[1])

def run(name):
    if not isfile(name):
        print("BrainFuck: file '%s' not found" % name)
    else:
        fp = open(name, 'r')
        program = fp.read()
        ptr, stack, sp = 0, [0] * len(program), 0
        paper = [0] * len(program)
        for p in range(len(program)):
            if (not sp) and (program[p] == ']'):
                print('BrainFuck: sp is zero')
                break
            if program[p] == '+':
                paper[ptr] += 1
            elif program[p] == '-':
                paper[ptr] -= 1
            elif program[p] == '[':
                stack[sp] = p
                sp += 1
            elif program[p] == ']':
                p = stack[sp - 1] if paper[ptr] else p
                sp -= (not paper[ptr])
            elif program[p] == ',':
                paper[ptr] = input()
            elif program[p] == '.':
                if isinstance(paper[ptr], str):
                    print(paper[ptr])
                else:
                    try:
                        print(chr(paper[ptr]))
                    except:
                        pass
            if (ptr >= len(program)) or (ptr < 0):
                print('BrainFuck: paper out of range')
                break
            if sp >= len(program):
                print('BrainFuck: sp out of range')

if __name__ == '__main__':
    main()

