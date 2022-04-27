#!/usr/bin/env python3

import requests
import os
import time
from html import escape
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.lib.units import mm
from reportlab.platypus import SimpleDocTemplate, Table, Paragraph, Image, Spacer, PageBreak

with open('pic.jpg', 'wb') as handle:
    response = requests.get("https://www.gdpicture.com/wp-content/uploads/gdpicture-mrz-ICAO.png", stream=True)
    for block in response.iter_content(1024):
        if not block:
            break
        handle.write(block)

start = time.time()
doc = SimpleDocTemplate("sample.pdf", pagesize=A4)
# container for the 'Flowable' objects
elements = []

styles = getSampleStyleSheet()
elements.append(Paragraph(escape("Title"),styles["Title"]))
elements.append(Paragraph(escape("HEading heading heading"),styles["Heading2"]))
elements.append(Paragraph(escape("Normal normal normal"),styles["Normal"]))

elements.append(Spacer(width=0, height=5*mm))

data= [['name', 'Foo Bar', 'FOO BAR'],
['ölksdf lösdkf ', '12.12.2022', '13.12.2022'],
['name sdf', 'Foo Bar', 'FOO BAR'],
['name ggsdre', 'Foo Bar', 'FOO BAR'],]
t=Table(data)
elements.append(t)

elements.append(PageBreak())

img = Image(os.path.realpath('pic.jpg'), width=None, height=None, mask=None)
a4_height, a4_width = A4
img._restrictSize(a4_height * 0.8, a4_height * 0.8)
elements.append(img)

elements.append(PageBreak())
elements.append(img)

# write the document to disk
doc.build(elements)
diff = (time.time() - start) * 1000
print(f"generation took {diff:.1f} ms")