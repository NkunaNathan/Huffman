# Huffman

1 Description
The American Standard Code for Information Exchange (ASCII) represents characters by a string of 7 bits.
The letter A is represented by the bit string 1000001 (65), B by 1000010 (66) and so on. There is room for 128
characters including lower-case and special characters. Over time, ASCII has been superseded by the newer
UTF-8 character encoding. ASCII characters were included in UTF-8 as the first 128 characters, which means
that UTF-8 is backwards compatible with ASCII.
Data compression is an important technique used in data storage and transmission over communication
networks. There are 2 basic types of compression: lossy and lossless. This involves how well the data can be
decoded. Lossless compression means that absolutely no information is lost in the coding/decoding process.
For example, files that are compressed with zip compression are lossless. You would use this type of compression
when errors in decoding are unacceptable – eBook/text formats for example. The file you compress
is exactly what you get when you unzip it. Lossy compression methods, on the other hand, are allowed to
discard some information in order to make the file smaller. Many video (MPEG, OGG, H.264/H.2651) and
audio (MP3) compression formats are lossy. They rely on the fact that our brains can make up for the lost
information or that there are parts of the data that we cannot sense. MP3 for example, drops many of the high
frequencies that a layperson wouldn’t notice anyway. The more frequencies it drops, the less information we
need to store and the smaller file becomes. On the other hand WAV and FLAC (open source) are a lossless
audio compression formats. In the context of Audio/Visual compression, we often speak in terms of a codec,
which stands for coder-decoder – or compressor-decompressor (depending on who you ask).
Huffman coding is an entropy encoding algorithm used for lossless data compression. Think of entropy as
a measure of randomness or uncertainty. Huffman encoding replaces the codes of characters that appear most
frequently with shorter codes. Huffman codes have the nice property that, if the weights are sorted, the time it
takes to encode or decode a message is linear in the length of the message to be encoded. In general, however,
Huffman encoding takes O(n log n).
The key to Huffman coding is the so-called prefix constraint, i.e. the code for any character may not be the
prefix of any other code. For example, if the string 001 is the code for some character, then no other code starts
with 001. A Huffman Code is an optimal prefix code that guarantees unique decodability of a file compressed
using the code. The code was devised by David A. Huffman at MIT in the early 1950s. Huffman coding is a
technique for assigning binary sequences to elements of an alphabet. The goal of an optimal code is to assign
the minimum number of bits to each symbol in the alphabet, given some frequency distribution.
This results in a Variable Length Code, where characters that appear often use fewer bits than characters
that rarely appear at all. For example, if we know that the letter e appears more often than the letter z we
should try to use fewer bits to represent e than we do z. ASCII and UTF-8 are examples of Fixed Length Codes
as every letter uses the same number of bits regardless of how many actually occur in a text – 7 or 8 respectively.
In this project, you will have to implement a system that allows encoding/decoding of messages into and
from Huffman code.

Encoder
The first program should accept a string from stdin. It should then calculate the frequency of each letter and
build the binary tree necessary to perform Huffman encoding. When calculating the priority of a leaf, it should
be done by the frequency, ties should then be broken in increasing order of the relevant ASCII/UTF-8 code.
When the frequencies have been calculated, print the priority queue characters, separated by spaces. On the
next line, print the frequencies. Print them in increasing order of priority. On the next line, you should print
out the encoded string. Following that, print out the number of bits used if characters are represented in 8-bit
UTF-8 (compatible with ASCII). The next line should contain the number of bits used in the encoded string.
The input string will only ever contain lower case letters and a spaces. No other ASCII characters will be
given.
Based on the she sells sea shells by the sea shore example above, here is some sample
input and output:
Sample Input:
she sells sea shells by the sea shore
Sample Output:
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
Decoder
The second program should read the first two lines of text from the first programs output. It first reads a line
with all the characters in increasing order or priority. The next line has the respective frequencies for these
characters. Once these lines have been read, the Huffman Tree can be reconstructed by using the exact
same process from the encoder. Next your program should read the line containing the encoded string. Your
program needs to decode the string by using the Huffman tree and output the decoded text followed by a new
line. The program can ignore all other input.
Sample Input:
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
Sample Output:
she sells sea shells by the sea shore


4 Linux Pipes
The Linux operating system provides a mechanism for programs to communicate using pipes. Imagine a pipe
consists of 2 queues. One from A to B and another from B to A. We can connect stdout of one program
to stdin of another by using the pipe operator (j) in the terminal. So if you have both programs coded and
working correctly, you should be able to do this:
echo she sells sea shells by the sea shore | ./encode | ./decode
This calls the echo command, which just outputs she sells sea shells by the sea shore
to stdout. We then pipe that into stdin of ./encode. We take the stdout of encode and pipe that into
decode.
