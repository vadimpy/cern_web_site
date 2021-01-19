from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('main/', views.main, name='main'),
    path('docs/', views.docs, name='docs'),
    path('wall/', views.wall, name='wall')
]