from django.db import models

class DHT11(models.Model):
    temperature = models.FloatField()
    humidite = models.FloatField()
    date_creation = models.DateTimeField(auto_now_add=True)

def __str__(self):
    return f"{self.temperature} °C - {self.humidite} %"