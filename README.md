# bookr
PSP book reader.

Forked from http://dl.qj.net/psp/homebrew-applications/bookr-v81.html .

Main modifications for now:
* Include "minutes remaining" battery indication.
* Support the Greek language for plain text files. Right now this means that all files are read in UTF8 encoding but they are converted to ISO-8859-7 encoding internally. Supporting Unicode internally will take a while given the architecture of the code.

__NOTE:__ Since the internal encoding is hard-coded to ISO-8859-7 right now it means you will not be able to read languages which are covered by the ISO-8859-1 encoding (even though in the version I forked it was possible). [Check wikipedia](https://en.wikipedia.org/wiki/ISO/IEC_8859-1#Coverage) for a list of those languages. Soon Uniocde will be used internally so all languages will be supported.
