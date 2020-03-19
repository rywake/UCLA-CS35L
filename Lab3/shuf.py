
import random, sys, argparse

class shuf:
  ## Initializes variable specific to the object of type class ##
    def __init__(self, headcount, repeat, rnge, Input):
        self.headcount = int(headcount)
        self.repeat = repeat
        self.Input = Input
        self.rnge = rnge

   ## Shuffles list ##    
    def shuffle(self):
        random.shuffle(self.Input)

  ## Prints out the correct number of lines ##
    def printlines(self):
        if self.headcount > len(self.Input):
            self.headcount = len(self.Input)
        for input_lines in range(0,self.headcount):
            print(self.Input[input_lines]) 

   ## Creates a list of numbers of range inputted ##    
    def create_range(self):
        lower = int(self.rnge[0])
        upper = int(self.rnge[1])
        while (lower < upper+1):
            self.Input.append(lower)
            lower += 1
        random.shuffle(self.Input)
        
   ## If the repeat function is activated ##
    def print_repeat(self):
        rep_range = self.headcount
        for loop in range(0,rep_range):
            print(random.choice(self.Input))


def main():
    version_msg = "%prog 1.0.0" 
    usage_msg = """%prog [OPTION] [-r] [-i] [-n] FILE"""

parser = argparse.ArgumentParser()

##Parses the arguments into the correct option and checks to make sure inputted values are correct ##
parser.add_argument("-i", "--input-range", action="store", dest="rnge", default="", help="Treat each number LO-HI as an input line.")
parser.add_argument("-n","--head-count", action="store", type=int, dest="headcount", default=sys.maxsize, help="Output at most COUNT lines")
parser.add_argument("-r","--repeat", action="store_true", dest="repeat", default=False, help="Lines can be outputted and repeated multiple times")
parser.add_argument("filename", action="store", nargs="?")
   
args = parser.parse_args()

input_ = []

## Both range and filename was given ###
if args.rnge != "" and args.filename != None:
    sys.exit("Error, both input-range and file given")

##Checks if no files and read in stdin ##
if ((args.filename is None or args.filename == "-") and args.rnge == "") :
    input_ = sys.stdin.read().splitlines()

##Checks and reads in the text file ##
if args.filename is not None:
        f = open(args.filename, "r")
        input_ = f.read().splitlines()
        f.close()

## Checks to make sure the headcount is valid"
if args.headcount is not None:
    try:
        headcount = int(args.headcount)
    except:
        parser.error("Invalid Headcount: {0}".
                        format(args.headcount))
    if args.headcount < 0:
        sys.exit("Invalid Headcount, Negative input given")

## No headcount argument was given ##
elif args.headcount is None:
    headcount = sys.maxsize

## Checks to see if an input-range was given ##
if args.rnge == "":
    splice_rnge = ""

## --input-range command was given in the argument ###
elif args.rnge != "":
    splice_rnge = args.rnge.split("-", 1)    
    try:
        int(splice_rnge[0])
        int(splice_rnge[1])
    except:
        parser.error("Invalid input-range". format(args.rnge))

### Checks to see if first input int is less than second ##
if args.rnge != "" and (int(splice_rnge[0]) > int(splice_rnge[1])):
    sys.exit("Error, invalid input-range")

## Creates a class variable to execute the commands ##
execute = shuf(args.headcount, args.repeat, splice_rnge, input_)

## Checks if -i flag is called ##
if execute.rnge != "":
    execute.create_range()
    execute.shuffle()
else:
    execute.shuffle()

## Checks if repeat flag is called ##
if (args.repeat is False):
    execute.printlines()
else:
    execute.print_repeat()

