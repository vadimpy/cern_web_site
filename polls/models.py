from django.db import models

class Documents(models.Model):
    doc_file = models.FileField('file path', upload_to='polls/static/')
    pub_datetime = models.DateTimeField('date published')
    doc_name = models.CharField(max_length=100)

class Wall(models.Model):
    pub_datetime = models.DateTimeField('date published')
    doc_file = models.FileField('file path', upload_to='polls/static/')
    doc_name = models.CharField(max_length=100)
    text = models.TextField('news text')