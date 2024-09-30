def search_keyword_in_sequence(keyword, sequence):
    if keyword.upper() in sequence.upper():
        return True
    return False


def read_fasta(filename):
    sequences = {}
    lines=[]
    with open(filename, 'r') as file:
        identifier = None
        sequence = ''
        buffer=0
        name=''
        for line in file:
            line = line.strip()
            lines.append(line)
            #print(line)
            if buffer==1 and not line.startswith('>'):
                 sequences[name]+=line
                 sequences[name]+="\n"
                
            elif line.startswith('>'):
                buffer=0
                name=''
                if identifier and search_keyword_in_sequence('electron', sequence):
                    #print(sequence)
                    buffer=1
                    sequences[identifier] = ""
                    name=identifier 
                sequence = ''
                sequence += line    
                identifier = line[1:]
        # 处理最后一个序列
        
        if identifier and search_keyword_in_sequence('electron', sequence):
                    sequences[identifier] = ""
                    for line in reversed(lines):
                        if line==sequence:
                            break
                        sequences[identifier]+=line
                        sequences[identifier]+="\n"
                   

                    
                    
                    
    return sequences

def count_letters(sequence):
    letter_count = {}
    for letter in sequence:
        if letter.isalpha():
            letter = letter.upper()  # 将字母统一转换为大写
            if letter in letter_count:
                letter_count[letter] += 1
            else:
                letter_count[letter] = 1
    return letter_count
print("hello")
fasta_file = "proton-transporting_ATPase.fasta"
sequences = read_fasta(fasta_file)

# 打印读取的序列
for identifier, sequence in sequences.items():
    print("Identifier:", identifier)
    print("Sequence:", sequence)
     
output_file = "proton-transporting_ATPase_with_electron.txt"
total_letter_count = {}
buffer=0
with open(output_file, 'w') as file:
    for identifier, sequence in sequences.items():
        buffer+=1
        file.write(">" + identifier + "\n")
        file.write(sequence)
        letter_count = count_letters(sequence)
        for letter, count in letter_count.items():
            file.write(f"{letter}: {count} ")
            buffer+=count
            if letter in total_letter_count:
                total_letter_count[letter] += count
            else:
                total_letter_count[letter] = count
        max_key = max(letter_count, key=letter_count.get)
        max_value = letter_count[max_key]
        file.write("\n")
        file.write("The biggest is "+max_key +" "+str(max_value)+"\n")
        file.write("\n")
    sorted_counts = sorted(total_letter_count.items(), key=lambda x: x[1], reverse=True)
    for letter, count in sorted_counts:
        file.write(f"{letter}: {(count/buffer)*100} "+"\n")
        
    
    #max_key = max(total_letter_count, key=total_letter_count.get)
    #max_value = total_letter_count[max_key]
    #file.write("The biggest is "+max_key +" "+str(max_value)+"\n")
    #file.write("Total "+str(buffer)+"\n")
        

print("Data written to", output_file)