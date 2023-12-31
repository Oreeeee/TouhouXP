"""
This utility patches MajorOperatingSystemVersion and MajorSubsystemVersion
headers of EXE files to 0x05 to make them run on NT 5.0
"""
import sys

MOSV_OFFSET = 64
MSV_OFFSET = 72
NT5_MAJOR = b"\x05"


def main() -> int:
    if len(sys.argv) != 2:
        print("Usage: {} <file_to_patch>".format(sys.argv[0]))
        return 1

    file_to_patch: str = sys.argv[1]
    with open(file_to_patch, "r+b") as f:
        # Search for the PE offset
        pe_offset: int = 0
        searching_for_pe: bool = True
        while searching_for_pe:
            pe_offset += 1
            f.seek(pe_offset)
            if f.read(2) == b"PE":
                searching_for_pe = False

        # Patch MajorOperatingSystemVersion
        f.seek(pe_offset + MOSV_OFFSET)
        f.write(NT5_MAJOR)

        # Patch MajorSubsystemVersion
        f.seek(pe_offset + MSV_OFFSET)
        f.write(NT5_MAJOR)


if __name__ == "__main__":
    sys.exit(main())
