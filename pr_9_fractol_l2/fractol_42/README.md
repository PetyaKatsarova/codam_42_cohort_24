<h1 align="center">fract'ol</h1>

<h2>Description</h2>
<p><strong>fract'ol</strong> is a project from the 42 cursus that involves creating a program to visualize various fractals, such as the Mandelbrot set, the Julia set, and others. The main objective is to learn more about complex numbers, fractal mathematics, and graphical rendering using the MLX42 library.</p>

<table>
	<tr>
		<td align="center"><img src="https://github.com/PaLucena/fract-ol/blob/main/img/mandelbrot.PNG"></td>
		<td align="center"><img src="https://github.com/PaLucena/fract-ol/blob/main/img/julia.PNG"></td>
		<td align="center"><img src="https://github.com/PaLucena/fract-ol/blob/main/img/burningship.PNG"></td>
	</tr>
</table>

<h2>Table of Contents</h2>
<ul>
    <li><a href="#requirements">Requirements</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#project-structure">Project Structure</a></li>
    <li><a href="#license">License</a></li>
</ul>

<h2 id="requirements">Requirements</h2>
<p>To compile and run the project, you will need:</p>
<ul>
    <li>A Unix operating system (Linux or macOS).</li>
    <li>gcc or any C compiler.</li>
    <li>Make.</li>
    <li>MLX42 library.</li>
    <li>GLFW library.</li>
</ul>

<h2 id="installation">Installation</h2>
<p>Clone the project repository and navigate to the main directory:</p>
<pre><code>git clone https://github.com/PaLucena/fract-ol.git
cd fract-ol</code></pre>
    <p>Compile the project using the included Makefile:</p>
    <pre><code>make</code></pre>
    <p>This will generate the <code>fractol</code> executable in the current directory.</p>

<h2 id="usage">Usage</h2>
<p>To start the fractal visualizer, run the following command:</p>
<pre><code>./fractol &lt;fractal_name&gt;</code></pre>
<p>Where <code>&lt;fractal_name&gt;</code> can be one of the following:</p>
<ul>
    <li><code>mandelbrot</code></li>
    <li><code>julia</code></li>
    <li><code>burningship</code></li>
</ul>
<p>Example:</p>
<pre><code>./fractol mandelbrot</code></pre>

<h2 id="features">Features</h2>
<p>The fract'ol program supports various features to enhance the fractal visualization experience:</p>
<ul>
    <li>Zoom in and out with the mouse scroll.</li>
    <li>Move the view using the arrow keys.</li>
    <li>Change the color scheme with the numeric keys.</li>
    <li>Switch between different fractals.</li>
</ul>

<h2 id="project-structure">Project Structure</h2>
<p>The project is organized into the following files and directories:</p>
<ul>
    <li><code>src/</code>: Contains the source code of the fractal visualizer.</li>
    <li><code>include/</code>: Contains the header files.</li>
    <li><code>Makefile</code>: Build script to generate the executable.</li>
    <li><code>README.md</code>: Project documentation.</li>
</ul>

<h2 id="license">License</h2>
<p>This project is licensed under the MIT License. See the <code>LICENSE</code> file for more details.</p>
