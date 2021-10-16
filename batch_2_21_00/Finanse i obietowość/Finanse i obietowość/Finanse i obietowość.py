import csv

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

html = """
<!DOCTYPE html>
<html>
<head>
<style>
table {
  font-family: arial, sans-serif;
  border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}

tr:nth-child(even) {
  background-color: #dddddd;
}
</style>
</head>
<body>

"""

html += "<table>"
html += "<tr>"
for col in cols:
    html += "<th>" + col + "</th>"
html += "</tr>"

for row in data:
    html += "<tr>"
    for i in range(len(row)):
        html += "<td>" + str(row[i]) + units[i] + "</td>"
    html += "</tr>"
    
html +="</table>"

html += """
</body>
</html>
"""

table_filename = "tabela.html"
html_file= open(table_filename,"w")
html_file.write(html)
html_file.close()