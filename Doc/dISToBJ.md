
# A quick start in dISToBJ

\mainpage

 \section intro_sec Overview

 The most important constructs.

 \subsection Globals

- with srdev::cast it exists a consistent way to cast one type to another.

 \subsection Namespaces

- srdev::Test is the namespace where all test are in

 \subsection Classes

- srdev::Base is the base class of everything. 
- srdev::Value is the base of all supported value types. 
- srdev::Property modulates a the srdev::Property from an srdev::Object

[Go to the graphical class hierarchy](inherits.html)

\addtogroup Base

This module contains basic constructs like srdev::Base or srdev::cast

\ref markdown

\page markdown Markdown Syntax
\htmlonly
 <iframe src="../markdown-guide.pdf" width="100%" scrolling="no" frameborder="0" id="lieferdatenbanken.iframe">markdown</iframe> 

<script>
var iframe = document.getElementById("lieferdatenbanken.iframe");    
iframe.onload = function(){  iframe.style.height = (iframe.offsetParent.offsetHeight - iframe.offsetHeight - 30) + 'px'; }
window.onresize = function(){   iframe.style.height = ( window.innerHeight - 200) + 'px'; }
</script>

\endhtmlonly
