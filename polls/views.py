from django.http import HttpResponse
from django.shortcuts import redirect, render
from .models import *
from json import dumps

def pass_to_vue(context):
    return {"vue_data" : dumps(context)}

def index(request):
    return redirect("main")

def main(request):
    context = {"message" : "done!"}
    return render(request, "main.html", pass_to_vue(context))

def docs(request):
    context_docs = [(o.doc_name, o.doc_file) for o in Documents.objects.all()]
    context = {"docs" : context_docs}
    return render(request, "docs.html", context)

def wall(request):
    context = {"docs" : [(o.text, o.doc_name, o.doc_file) for o in Wall.objects.all()]}
    return render(request, "wall.html", context)