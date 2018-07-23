from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class Thread(models.Model):
    name = models.CharField(max_length=100)
    description = models.CharField(max_length=5000)
    created_on = models.DateTimeField('created on')
    
    def __str__(self):
        return self.name

class Message(models.Model):
    thread_id = models.ForeignKey(Thread, on_delete=models.CASCADE)
    user_id = models.ForeignKey(User, on_delete=models.SET_NULL, null=True)
    content = models.CharField(max_length=5000)
    created_on = models.DateTimeField('created on')
    
    def __str__(self):
        return self.content[:100]
