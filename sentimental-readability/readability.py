from cs50 import get_string

text = get_string("Input Text: ")

letters = 0
words = 1
sentences = 0
# find the number of letters, words and sentences
for i in range(len(text)):
    if (64 < ord(text[i]) and ord(text[i]) < 91) or (96 < ord(text[i]) and ord(text[i]) < 123):
        letters += 1
    if (ord(text[i]) == 32):
        words += 1
    if (ord(text[i]) == 33 or ord(text[i]) == 46 or ord(text[i]) == 63):
        sentences += 1

# print(letters, words, sentences)
# calculate Coleman-Liau index
L = 0.0588 * letters / words * 100
S = 0.296 * sentences / words * 100
index = L - S - 15.8
grade = round(index)

# output
if grade < 1:
    print("Before Grade 1\n")
elif grade >= 16:
    print("Grade 16+\n")
else:
    print("Grade %i\n", grade)
