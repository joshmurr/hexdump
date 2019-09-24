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
            for integer in b:
                if offset % 16 == 0:
                    print()
                    print(f'{offset:08x}  ', end='')
                if offset % 8 == 7:
                    print(f'{integer:02x}  ', end='')
                else:
                    print(f'{integer:02x} ', end='')

                offset += 1
            print('*')

if __name__ == "__main__":
    main()
