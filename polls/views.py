from django.http import HttpResponse
from django.shortcuts import redirect, render
from json import dumps

def pass_to_vue(context):
    return {"vue_data" : dumps(context)}

def index(request):
    return redirect("main")

def main(request):
    context = {"message" : "done!"}
    return render(request, "main.html", pass_to_vue(context))

def docs(request):
    context = {"docs" : [
        ("Устав партнёрства", "vue.js"),
        ("Внутренний регламент", "vue.js"),
        ("Протокол", "vue.js"),
        ("Слава бюрократии", "vue.js"),
    ]}
    return render(request, "docs.html", context)

def wall(request):
    context = {"docs" : [
        ("Устав партнёрства", "cfa.pdf"),
        ("Внутренний регламент", "excel.xlsx"),
    ]}
    return render(request, "wall.html", context)