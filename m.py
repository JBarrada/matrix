

cube = [(-1, -1, 0), (-1, 1, 0), (1, 1, 0), (1, -1, 0),
        (-1, -1, 2), (-1, 1, 2), (1, 1, 2), (1, -1, 2)]

# modelspace -> worldspace -> viewspace -> projectionspace


def mmult44x14(m44, m14):
    product = [[0.0] for i in range(4)]
    for m44_row in range(4):
        for m_pos in range(4):
            product[m44_row][0] += m44[m44_row][m_pos]*m14[m_pos][0]
    return product

test44 = [[1, 0, 0, 0],
          [0, 1, 0, 0],
          [0, 0, 1, 1],
          [0, 0, 0, 1]]

test14 = [[0],
          [0],
          [1.5],
          [1]]

print mmult44x14(test44, test14)
