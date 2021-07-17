'''
Conan file docs: https://docs.conan.io/en/latest/reference/conanfile.html
'''

from conans import ConanFile, CMake, tools

class Tetris(ConanFile):
	name = 'hs_tetris'
	license = 'MIT'
	author = 'Patrick Crabtree <pconnorcrabtree@gmail.com>'
	url = 'https://github.com/ThePatrickCrab/tetris'
	description = 'Highschool tetris project'
	settings = 'os', 'compiler', 'build_type', 'arch'
	default_options = 'sfml:graphics=True', 'sfml:window=True'
	generators = 'cmake'
	exports_sources = 'CMakeLists.txt', 'include/*', 'src/*', 'resources/*'
	requires = 'sfml/2.5.1'

	def _configure_cmake(self):
		cmake = CMake(self)
		cmake.configure()
		return cmake

	def build(self):
		cmake = self._configure_cmake()
		cmake.build()

	def package(self):
		cmake = self._configure_cmake()
		cmake.install()
