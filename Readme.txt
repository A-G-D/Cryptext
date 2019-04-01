Cryptext v1.2.1


CREATING AN ENCRYPTED TEXT

Text Files can be found under "Texts" folder, with a ".txt" extension.
To be able to create a text file, create a translation file first.
It will be saved under the "Translations" folder with a ".trln"
extension. This extension refers to raw translation files. You can
then select which of these raw translations you want to use for your
text file. After saving, the program will generate an encrypted
translation copy of the raw translation file used, which can be found
under the same directory and name with the text file, only with a
different extension (".ckey"). This encrypted translation is
considered the KEY. This is what you would share to others for them
to decipher the message of your text files while at the same time,
remaining oblivious to the actual details of the translation itself.


READING AN ENCRYPTED TEXT

To be able to decipher the message of an encrypted text file, you
need the actual file and its key file (which have the extensions
".txt" and ".ckey" respectively). The file names of the text file and
its key must be similar and you must put them into a folder with the
same name also. Then, put their folder inside the "Texts" folder.
After this, the program will be able to locate and read the encrypted
text file.


COMMAND-LINE ARGUMENTS
"-basicstyle" - Disables visual styles for the application
"-load" "$FILE_PATH$" - Opens the text creation window while loading
the contents of the specified file