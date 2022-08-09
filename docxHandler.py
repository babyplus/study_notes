import sys
from docx import Document
from docx.shared import RGBColor
from docx.shared import Pt
from docx.enum.text import WD_ALIGN_PARAGRAPH

sample = '''
sample:
    python docxHandle.py syslog
'''
if (len(sys.argv) == 2):
    target = sys.argv[1]
else:
    print("command error")
    print(sample)
    exit(1)

doc = Document("{}/README.docx".format(target))
style = doc.styles["Source Code"]
style.font.shadow = True
style.font.color.rgb = RGBColor(0xFF, 0x00, 0xFF)
style = doc.styles["Image Caption"]
style.paragraph_format.alignment = WD_ALIGN_PARAGRAPH.CENTER
style.font.color.rgb = RGBColor(0xAA, 0xAA, 0xAA)

for para in doc.paragraphs:
    para.paragraph_format.line_spacing = 1.5
    if (para.style.name == "First Paragraph"):
        para.style = "Body Text"
doc.save(r"{}/README.docx".format(target))
