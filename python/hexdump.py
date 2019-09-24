import sys
import filetype


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: hexdump.py <file>")

    infile = sys.argv[1]
    kind = filetype.guess(infile)
    if kind is None:
        print('Cannot guess filetype')
        return 1

    with open(infile, 'rb') as readfile:
        print("Checking file of type %s" % kind.extension)
        print()

        offset = 0

        for b in readfile:
            line = []
            print(f'{offset:08x}', end='')
            for integer in b:
                if offset % 16 == 15:
                    print(f" {integer:02x}  |", end='')
                    for c in line:
                        if c < 127 and c > 0:
                            try:
                                print(str(chr(c)), end='')
                            except ValueError:
                                print('.', end='')
                        else:
                            print('.', end='')
                    print('|')
                    # Newline
                    print(f'{offset+1:08x}', end='')
                    line.clear()
                elif offset % 8 == 0:
                    # 17 % 9 == 8
                    print(f'  {integer:02x}', end='')
                else:
                    print(f' {integer:02x}', end='')

                line.append(integer)
                offset += 1
            print('*')

if __name__ == "__main__":
    main()
