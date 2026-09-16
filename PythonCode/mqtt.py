import requests
import random
import time
from datetime import datetime

# -- Configuración del servidor --
server = "https://api.thingspeak.com/update"
apiKey = "2ZA8S8GJX6LL7LYI"
channelId = 3156518

# -- Generar numeros random --
while(True):
    ahora = datetime.now()                                                                                                                                            
    horas = ahora.strftime("%H")
    minutos = ahora.strftime("%M")
    print(ahora.strftime("%H%M"))
    params = {
        "api_key": apiKey,
        "field1": horas,
        "field2": minutos
    }

    # -- Leer la libreria   
    resp = requests.get(server, params=params, timeout=20)
    
    if resp.status_code == 200:
        print(f"tiempo enviado a ThingSpeak {horas} {minutos}")
    else:
        print(f"ERROR al enviar: {horas} {minutos}")
    time.sleep(60)