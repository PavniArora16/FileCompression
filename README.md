<h1>Huffman Encoding Using Min Heap</h1>

<h2>Overview</h2>
<p>
This project implements the Huffman Encoding algorithm in C to perform lossless text compression.
</p>

<p>
The program reads text from an input file, calculates the frequency of each character, builds a Huffman Tree using a Min Heap, generates Huffman codes, encodes the input text, and stores the compressed binary representation in an output file.
</p>

<hr>

<h2>Features</h2>

<ul>
    <li>Reads text from a file (<code>input.txt</code>)</li>
    <li>Calculates character frequencies</li>
    <li>Constructs a Huffman Tree using a Min Heap</li>
    <li>Generates unique Huffman codes for each character</li>
    <li>Encodes the input text</li>
    <li>Writes the encoded output to <code>output.txt</code></li>
    <li>Displays compression statistics including:
        <ul>
            <li>Original size</li>
            <li>Encoded size</li>
            <li>Memory saved</li>
            <li>Percentage reduction</li>
        </ul>
    </li>
</ul>

<hr>

<h2>Data Structures Used</h2>

<ul>
    <li>Binary Tree (Huffman Tree)</li>
    <li>Min Heap (Priority Queue)</li>
    <li>Arrays for frequency counting and code storage</li>
</ul>

<hr>

<h2>Project Structure</h2>

<pre>
.
├── program.c
├── input.txt
└── output.txt
</pre>

<ul>
    <li><code>program.c</code> → Source code</li>
    <li><code>input.txt</code> → Input text file</li>
    <li><code>output.txt</code> → Generated encoded output</li>
</ul>

<hr>

<h2>How It Works</h2>

<ol>
    <li>Read text from <code>input.txt</code></li>
    <li>Count frequency of each printable ASCII character</li>
    <li>Insert all characters into a Min Heap</li>
    <li>Repeatedly extract the two minimum-frequency nodes</li>
    <li>Merge them into a new node</li>
    <li>Build the Huffman Tree</li>
    <li>Generate Huffman codes by traversing the tree</li>
    <li>Encode the original text</li>
    <li>Save the encoded string to <code>output.txt</code></li>
    <li>Display compression statistics</li>
</ol>

<hr>

<h2>Compilation</h2>

<p>Using GCC:</p>

<pre>gcc program.c -o huffman</pre>

<hr>

<h2>Execution</h2>

<p>Run the program:</p>

<pre>./huffman</pre>

<p>Windows:</p>

<pre>huffman.exe</pre>

<hr>

<h2>Example Input</h2>

<p>Contents of <code>input.txt</code>:</p>

<pre>hello world</pre>

<hr>

<h2>Example Output</h2>

<p>Console Output:</p>

<pre>
Huffman Codes:
h = 1100
e = 1101
l = 01
o = 101

Original space required: 88 bits
Space required for encoded text: 32 bits
Memory saved: 56 bits, 63.64% reduction

Task Done!
</pre>

<p>Contents of <code>output.txt</code>:</p>

<pre>
Original text: hello world

Encoded string: 110011010101...
</pre>

<hr>

<h2>Time Complexity</h2>

<ul>
    <li>Frequency Counting: O(n)</li>
    <li>Heap Operations: O(k log k)</li>
    <li>Huffman Tree Construction: O(k log k)</li>
    <li>Encoding: O(n)</li>
</ul>

<p>
Where:
</p>

<ul>
    <li>n = length of input text</li>
    <li>k = number of unique characters</li>
</ul>

<hr>

<h2>Applications</h2>

<ul>
    <li>File Compression</li>
    <li>Data Transmission</li>
    <li>Text Encoding</li>
    <li>Lossless Data Storage</li>
    <li>Communication Systems</li>
</ul>

<hr>

