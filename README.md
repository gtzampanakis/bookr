# bookr
PSP book reader.

Forked from http://dl.qj.net/psp/homebrew-applications/bookr-v81.html .

Main modifications for now:
* Include indication for battery life in time in addition to the percentage.
* Support the Greek language. Right now this means that all files are opened in ISO-8859-7 encoding since supporting Unicode will take a while given the architecture of the code.

__NOTE:__ Since the encoding is hard-coded to ISO-8859-7 right now it means you will not be able to read languages which are covered by the ISO-8859-1 encoding (even though in the version I forked it was possible). [Check wikipedia](https://en.wikipedia.org/wiki/ISO/IEC_8859-1#Coverage) for a list of those languages. Soon there will be encoding selection in the options to fix this.
