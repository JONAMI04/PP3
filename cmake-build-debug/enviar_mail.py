import sys
import smtplib
import ssl
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def usage():
    print("Uso: python enviar_mail.py <nombre> <destinatario> <asunto> <cuerpo>")
    sys.exit(1)

if len(sys.argv) < 5:
    usage()

nombre = sys.argv[1]
destinatario = sys.argv[2]
asunto = sys.argv[3]
cuerpo = sys.argv[4]

EMAIL_USER = "biblioteca.pp3@gmail.com"
EMAIL_PASS = "xyqb itoy xjba umfv"

if not EMAIL_USER or not EMAIL_PASS:
    print("Error: configurar EMAIL_USER y EMAIL_PASS")
    sys.exit(1)

# Usamos MIMEText para texto simple, es lo más simple.
mensaje = MIMEText(cuerpo, "plain", "utf-8")
mensaje["Subject"] = asunto
mensaje["From"] = EMAIL_USER
mensaje["To"] = destinatario


try:
    # **CORRECCIÓN CLAVE:** Usar SMTP para puerto 587 y luego starttls()
    server = smtplib.SMTP("smtp.gmail.com", 587)
    context = ssl.create_default_context()
    server.starttls(context=context) # Encriptar la conexión

    server.login(EMAIL_USER, EMAIL_PASS)
    server.sendmail(EMAIL_USER, [destinatario], mensaje.as_string())
    server.quit()

    print(f"Correo enviado a {destinatario}")
    sys.exit(0)
except Exception as e:
    print("Error al enviar correo:", e)
    sys.exit(2)