
# A quick start in dISToBJ

\mainpage

 \section intro_sec Overview

 The most important constructs.

 \subsection Globals

- with srdev::cast it exists a consistent way to cast one type to another.

 \subsection Namespaces

- srdev is the namespace where all is in
- srdev::Test is the namespace where all test are in
- srdev::System is the namespace where all system classes are in

 \subsection Classes

- srdev::Base is the base class of everything. 
- srdev::Value is the base of all supported value types. 
- srdev::Property modulates a the srdev::Property from an srdev::Object

[Go to the graphical class hierarchy](inherits.html)

\ref markdown

\ref db-model

\addtogroup Base
This module contains basic constructs like srdev::Base or srdev::cast

\addtogroup Traits
This module contains traits and wrappers for object classes and instances.
- srdev::ObjectAccess< System::ObjectType >
- srdev::ObjectAccess< System::PropertyType >

\addtogroup Test
The test module contains uint tests for each construct.
Each test is inherited from srdev::Test::Case


\page markdown Markdown Syntax
\htmlonly
 <iframe src="External/markdown-guide.pdf" width="100%" scrolling="no" frameborder="0" id="markdown-guide.iframe">markdown</iframe> 

<script>
var iframe = document.getElementById("markdown-guide.iframe");    
iframe.onload = function(){  iframe.style.height = (iframe.offsetParent.offsetHeight - iframe.offsetHeight - 30) + 'px'; }
window.onresize = function(){   iframe.style.height = ( window.innerHeight - 200) + 'px'; }
</script>

\endhtmlonly

\page db-model ObjectDb 
\dotfile ObjectDb.dot "Object databse model" 