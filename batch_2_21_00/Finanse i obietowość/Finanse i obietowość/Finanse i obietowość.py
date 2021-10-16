import csv
import xlsxwriter

filename = 'faktura.csv'

with open(filename, 'r') as file:
    data = [row[0].split(sep=';') for row in csv.reader(file)]
    for i in range(len(data)):
        for j in range(1,len(data[i])):
            data[i][j] = eval(data[i][j])
            
cols = ['Nazwa produktu','Cena netto bez przecinka*','Podatek VAT','Narzut','Cena sklepowa']
units = ['','','%','%','']

def price(x):
    return round( (int(x[1])*0.01) * (1+(int(x[2])*0.01)) * (1+(int(x[3])*0.01)), 2)

for i in range(len(data)):
    x = price(data[i])
    data[i].append(x)
    
def Print(ele):
    for i in range(len(ele)):
        print(cols[i]," = ",ele[i],units[i],sep='')
        
        
for row in data:
    Print(row)
    print('----------------------------\n')
