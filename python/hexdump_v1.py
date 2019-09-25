import sys

def get_remainder(val, n):
    return n-(val%n)

def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: hexdump.py <file>")

    infile = sys.argv[1]

    with open(infile, 'rb') as readfile:
        offset = 0

        for b in readfile:
            line = []
            print(f"{offset:08x}", end='')
            for integer in b:
                if integer < 32:
                    line.append(0)
                else:
                    line.append(integer)

                if offset % 16 == 15:
                    print(f" {integer:02x}  |", end='')
                    for c in line:
                        if c <= 127 and c > 0:
                            try:
                                print(str(chr(c)), end='')
                            except ValueError:
                                print('.', end='')
                        else:
                            print('.', end='')
                    print('|')

                    # Newline
                    # print(line)
                    print(f'{offset+1:08x}', end='')
                    line.clear()
                elif offset % 8 == 0:
                    # 17 % 9 == 8
                    print(f'  {integer:02x}', end='')
                else:
                    print(f' {integer:02x}', end='')

                offset += 1

            print('*')


if __name__ == "__main__":
    main()
