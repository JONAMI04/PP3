import os
import sys
import smtplib
from email.mime.text import MIMEText

def usage():
    print("Uso: python enviar_mail.py <nombre> <destinatario> <asunto> <cuerpo>")
    sys.exit(1)

if len(sys.argv) < 5:
    usage()

nombre = sys.argv[1]
destinatario = sys.argv[2]
asunto = sys.argv[3]
cuerpo = sys.argv[4]

EMAIL_USER = os.getenv("EMAIL_USER")
EMAIL_PASS = os.getenv("EMAIL_PASS")

if not EMAIL_USER or not EMAIL_PASS:
    print("Error: configurar EMAIL_USER y EMAIL_PASS en las variables de entorno")
    sys.exit(1)

mensaje = MIMEText(cuerpo, _charset="utf-8")
mensaje["Subject"] = asunto
mensaje["From"] = EMAIL_USER
mensaje["To"] = destinatario

try:
    # Usar SMTP_SSL puerto 465 (Gmail) o ajustar si usa otro servidor/puerto
    with smtplib.SMTP_SSL("smtp.gmail.com", 587) as server:
        server.login(EMAIL_USER, EMAIL_PASS)
        server.sendmail(EMAIL_USER, [destinatario], mensaje.as_string())
    print(f"Correo enviado a {destinatario}")
    sys.exit(0)
except Exception as e:
    print("Error al enviar correo:", e)
    sys.exit(2)