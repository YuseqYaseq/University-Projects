from django.urls import path
from django.contrib import admin

from . import views

app_name = 'forum'
urlpatterns = [
    #main view
    path('', views.index, name='index'),
    
    #login
    path('lin/', views.lin, name='lin'),
    
    #Thread view
    path('<int:thread_id>/<int:page>/', views.thread, name='thread'),
    
    #register
    path('reg/', views.reg, name='reg'),
    
    #logout
    path('lout/', views.lout, name='lout'),
]
