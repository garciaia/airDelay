from gooey import Gooey, GooeyParser
import subprocess

@Gooey(program_name="airDelay")
def parse_args():
    gooey_options={'show_border': True,'columns':1}
    parser = GooeyParser(description="Demonstrates and Compares the performance of different graph implementations, Adjacency Matrix vs List")
    parser.add_argument("Origin Airport",help="Starting Airport")
    parser.add_argument("Destination Airport",help="Arrival Airport")
    parser.add_argument("Graph Data Structure",choices=['List', 'Matrix'],widget="Dropdown",help="To Use")
    return parser.parse_args()

args = parse_args()
args = str(args)
#print(args)
test = args
datastructure1 = test.find(":") + 3
datastructure2 = test.find(",") - 1
beg = test[datastructure1:datastructure2]
test = test[datastructure2+2:len(test)]
end1 = test.find(":") + 3
end2 = test.find(",") - 1
end = test[end1:end2]
test = test[end2+2:len(test)]
end1 = test.find(":") + 3
end2 = test.find("}") - 1
datastructure = test[end1:end2]
toInput = datastructure + "," + beg + "," + end

with open('input.txt', 'w') as f:
    f.write(toInput)

subprocess.run("./untitled", shell=False)

with open('output.txt') as f:
    lines = f.readlines()

print(lines)
