#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


from google.appengine.ext import webapp
from google.appengine.ext.webapp import util


class MainHandler(webapp.RequestHandler):

  def __init__(self):
    self.key="853b128a-0c18-42f2-835f-db9f5b6f7fb9"
    # version
    self.apiVersion=1

  def get(self):
    self.response.headers['Content-Type'] = 'text/xml'
    self.response.out.write('<SymbianSigned>')
    self.response.out.write('<UID3>')
    self.response.out.write('0xDEADBEEF')
    self.response.out.write('</UID3>')
    self.response.out.write('<description>')
    self.response.out.write('leviation application. Pretty cool, ahe?')
    self.response.out.write('</description>')
    self.response.out.write('</SymbianSigned>')

  def post(self): 
  	self.response.headers['Content-Type'] = 'text/xml'
  	self.response.out.write('<args>')
	self.response.out.write(self.request.query_string)
  	self.response.out.write('</args>')
  	self.response.out.write('<body>')
  	self.response.out.write(self.request.body)
  	self.response.out.write('</body>')
 

def main():
  application = webapp.WSGIApplication([('/', MainHandler)],
                                       debug=True)
  util.run_wsgi_app(application)


if __name__ == '__main__':
  main()
