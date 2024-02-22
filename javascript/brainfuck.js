const fs = require("fs");

const { EOL } = require("os");

const input = fs.readFileSync(process.argv[2], "utf8");

const buffer = Buffer.alloc(30000);

let d = 0;
let i = 0;

for (i = 0; i < input.length; i++) {
	switch(input[i]) {
		case ">":
			d++;
			break;
		case "<":
			d--;
			break;
		case "+":
			buffer[d]++;
			break;
		case "-":
			buffer[d]--;
			break;
		case ".":
			if (buffer[d] == 10) {
				process.stdout.write(EOL);
			} else {
				process.stdout.write(buffer.toString("ascii", d, d + 1));
			}
			break;
		case ",":
			fs.readSync(0, buffer, d, 1);
			if (buffer[d] == 10) buffer[d] = 0;
			break;
		case "[":
			if (buffer[d] == 0) {
				let count = 1;
				while (count > 0) {
					if (i == input.length) throw new EvalError("No matching ]");
					i++;
					if (input[i] == "[") {
						count++;
					} else if (input[i] == "]") {
						count--;
					}
				}
			}
			break;
		case "]":
			if (buffer[d] != 0) {
				let count = 1;
				while (count > 0) {
					if (i == 0) throw new EvalError("No matching [");
					i--;
					if (input[i] == "]") {
						count++;
					} else if (input[i] == "[") {
						count--;
					}
				}
			}
			break;
		case "#":
			// print debug information (buffer, d, i). use process.stdout.write to make bold
			process.stdout.write("\x1b[1mBuffer: \x1b[0m");
			console.log(buffer);
			process.stdout.write("\x1b[1mData Pointer: \x1b[0m");
			console.log(d);
			process.stdout.write("\x1b[1mInstruction Pointer: \x1b[0m");
			console.log(i);
			break;
	}
}