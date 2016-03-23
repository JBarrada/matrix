vectors = []
normals = []
faces = []

with open('pig.obj') as f:
    for line in f:
        if line.startswith('v '):
            vectors += [map(float, line.split()[1:4])]
        if line.startswith('vn '):
            normals += [map(float, line.split()[1:4])]
        if line.startswith('f '):
            temp_face = line.split()[1:4]
            face = []
            for p in temp_face:
                face += [int(p.split('/')[0])-1]
            face += [int(temp_face[0].split('/')[-1])-1]
            faces += [face]

vectorsstring = '(vector[]){'
for vector in vectors:
    vectorsstring += '{%f,%f,%f},' % (vector[0], vector[1], vector[2])
vectorsstring = vectorsstring[0:-1] + '}'

normalsstring = '(vector[]){'
for normal in normals:
    normalsstring += '{%f,%f,%f},' % (normal[0], normal[1], normal[2])
normalsstring = normalsstring[0:-1] + '}'

facesstring = '(triangle[]){'
for face in faces:
    facesstring += '{%d,%d,%d,%d},' % (face[0], face[1], face[2], face[3])
facesstring = facesstring[0:-1] + '}'

objstring = '{%d,%d,%d,%s,%s,%s,{4,4,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}};' % (len(vectors), len(normals), len(faces),
                                                                            vectorsstring, normalsstring, facesstring)

print objstring
