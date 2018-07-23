from django import forms
from django.core.exceptions import ValidationError

from django.contrib.auth.models import User
from django.contrib.auth import authenticate

class LoginForm(forms.Form):
    login = forms.CharField(max_length=100)
    password = forms.CharField(widget=forms.PasswordInput(), max_length=100)

class RegisterForm(forms.Form):
    username = forms.CharField(max_length=100)
    password = forms.CharField(widget=forms.PasswordInput(), max_length=100)
    password2 = forms.CharField(widget=forms.PasswordInput(), max_length=100, help_text="Repeat your password")
    name = forms.CharField(max_length=100, required=False)
    surname = forms.CharField(max_length=100, required=False)
    
    #1. username can't be taken
    #2. password must be at least 3 characters long
    #3. passwords must be identical
    def clean(self):
        username = self.cleaned_data['username']
        if User.objects.filter(username=username).exists():
            raise ValidationError('Username already registered!')
        
        password = self.cleaned_data['password']
        password2 = self.cleaned_data['password2']
        
        if password != password2:
            raise ValidationError('Passwords must be identical!')
        
        if len(password) < 4:
            raise ValidationError('Password is too short!')
        
        return self.cleaned_data

class MessageForm(forms.Form):
    content = forms.CharField(widget=forms.Textarea)
    
    #message cant be empty
    def clean_content(self):
        content = self.cleaned_data['content']
        if len(content) == 0:
            raise ValidationError('You are trying to submit an empty message!')
        return content
    
    #Let's set the text area to proper size
    def __init__(self, *args, **kwargs):
        super(MessageForm, self).__init__(*args, **kwargs) # Call to Form constructor
        self.fields['content'].widget.attrs['cols'] = 70;
        self.fields['content'].widget.attrs['rows'] = 10;

class ThreadForm(forms.Form):
    name = forms.CharField(max_length=100)
    description = forms.CharField(widget=forms.Textarea)
    












