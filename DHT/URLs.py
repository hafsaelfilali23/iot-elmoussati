from django.urls import path
from .views import coucou
from .api import Dlist, Dhtviews
urlpatterns = [
  path('get/', Dlist, name='get_mesures'),
  path('post/', Dhtviews.as_view(), name='post_mesure'),
]