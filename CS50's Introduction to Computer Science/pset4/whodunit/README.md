# Questions

## What's `stdint.h`?

is a header file to various integer types, and related macros, with size constraints.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

BMP file contains following types:
* `BYTE` - A BYTE is an 8-bit unsigned value that corresponds to a single octet in a network protocol -> `uint8_t`
* `DWORD` - A DWORD is a 32-bit unsigned integer (range: 0 through 4294967295 decimal) -> `uint32_t`
* `LONG` - A LONG is a 32-bit signed integer, in twos-complement format (range: –2147483648 through 2147483647 decimal) -> `int32_t`
* `WORD` - A WORD is a 16-bit unsigned integer (range: 0 through 65535 decimal) -> `uint16_t`

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* `BYTE` -> 1 byte
* `DWORD` -> 4 bytes
* `LONG` -> 4 bytes
* `WORD` -> 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

bfType for BMP file:
0x42 0x4D in hexadecimal
66 77 in decimal
B M in ASCII

## What's the difference between `bfSize` and `biSize`?

bfSize - The size, in bytes, of the bitmap file.
biSize - Specifies the number of bytes required by the structure (BITMAPINFOHEADER = 14 bytes).
This value does not include the size of the color table or the size of the color masks, if they are appended to the end of structure.

bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
bfSize = biSizeImage + 54
// since BITMAPFILEHEADER = 40 bytes and BITMAPINFOHEADER = 14 bytes
biSizeImage = (biWidth * sizeof(RGBTRIPLE) + padding) * abs(biHeight)

## What does it mean if `biHeight` is negative?

Specifies the height of the bitmap, in pixels.
For uncompressed RGB bitmaps, if biHeight is positive, the bitmap is a bottom-up DIB with the origin at the lower left corner.
If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount - The number of bits-per-pixel (0, 1, 4, 8, 16, 24, 32)

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file might not exist / some permission error occurred while accessing a file such as "Read-Only" or "Write-Protected"

## Why is the third argument to `fread` always `1` in our code?

We read 3 elements. Just 1 element at a time:
BITMAPFILEHEADER
BITMAPINFOHEADER
RGBTRIPLE

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Each row (aka "scanline") in BMPs is a multiple of 4.
The scanline is "padded" with as many zeroes as it takes to extend the scanline’s length to a multiple of 4

## What does `fseek` do?

Allows you rewind or fast-forward within a file.

## What is `SEEK_CUR`?

SEEK_CUR - Current position of the file pointer
