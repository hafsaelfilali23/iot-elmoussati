from .models import DHT11
from .serializers import DHT11Serializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import generics

# GET : lire les mesures
@api_view(['GET'])
def Dlist(request):
    all_data = DHT11.objects.all()
    data = DHT11Serializer(all_data, many=True).data
    return Response({'data': data})

# POST : enregistrer une nouvelle mesure
class Dhtviews(generics.CreateAPIView):
    queryset = DHT11.objects.all()
    serializer_class = DHT11Serializer