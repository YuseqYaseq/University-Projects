from django.shortcuts import render, redirect
from django.http import HttpResponse, HttpResponseRedirect, Http404
from django.contrib.auth import authenticate, login, logout
from django.template import loader
from django.urls import reverse
from django.contrib.auth.decorators import login_required

from .forms import LoginForm, RegisterForm, MessageForm, ThreadForm
from .models import Thread, Message
from django.contrib.auth.models import User

import datetime

@login_required(login_url='forum:lin')
def index(request):
    #see if a new thread has been created
    if request.method == 'POST':
        form = ThreadForm(request.POST)
        if form.is_valid():
            thread = Thread.objects.create(name=form.cleaned_data['name'], description=form.cleaned_data['description'], created_on=datetime.datetime.now())
            thread.save()
    threads = Thread.objects.order_by('-created_on')
    template = loader.get_template('forum/index.html')
    context = {
        'threads': threads,
        'form': ThreadForm(),
    }
    return HttpResponse(template.render(context, request))

@login_required(login_url='forum:lin')
def thread(request, thread_id, page):
    #see if a message has been submitted
    if request.method == 'POST':
        form = MessageForm(request.POST)
        if form.is_valid():
            msg = Message.objects.create(thread_id=Thread.objects.filter(id=thread_id).get(), user_id=request.user, content=form.cleaned_data['content'], created_on=datetime.datetime.now())
            msg.save()
    
    messages_per_page = 5
    template = loader.get_template('forum/thread.html')
    #get messages from the nth page
    num_of_messages = Message.objects.all().count()
    messages = Message.objects.filter(thread_id=thread_id).order_by('created_on')[page*messages_per_page:page*messages_per_page+(messages_per_page)]
    thread_title = Thread.objects.filter(id=thread_id).get().name
    context = {
        'page': page,
        'messages': messages,
        'thread_id': thread_id,
        'thread_title': thread_title,
        'form': MessageForm(),
    }
    if (page+1)*messages_per_page < num_of_messages:
        context['next_page'] = page+1
    if page > 0:
        context['prev_page'] = page-1
    return HttpResponse(template.render(context, request))

def lin(request):
    if request.method == 'POST':
        form = LoginForm(request.POST)
        if form.is_valid():
            user = authenticate(request, username=form.cleaned_data['login'], password=form.cleaned_data['password'])
            if user is None:
                return render(request, 'forum/login.html', {'form':form, 'pass_incorrect':True})
            login(request, user)
            return HttpResponseRedirect(reverse('forum:index'))
    else:
        form = LoginForm()
    return render(request, 'forum/login.html', {'form':form, 'pass_incorrect':False})

def lout(request):
    logout(request)
    return HttpResponseRedirect(reverse('forum:lin'))

def reg(request):
    if request.method == 'POST':
        form = RegisterForm(request.POST)
        if form.is_valid():
            username = form.cleaned_data['username']
            password = form.cleaned_data['password']
            name = form.cleaned_data['name']
            surname = form.cleaned_data['surname']
            user = User.objects.create_user(username=username, password=password, first_name=name, last_name=surname)
            user.save()
            
            return HttpResponseRedirect(reverse('forum:lin'))
    #if nothing has been submitted yet, we need to return an empty form
    else:
        form = RegisterForm()
    return render(request, 'forum/reg.html', {'form':form})


