<?hh // strict
namespace Fastuc\View;

class Finder
{
	const DEFAULT_FILE_EXTENSION = '.hh';

	private Vector<string> $searchPaths;

	private Map<string, string> $cachedPaths;

	public function __construct()
	{
		$this->searchPaths = Vector<string> { '.' };
		$this->cachedPaths = new Map<string, string>;
	}

	/**
	 * @param string $path
	 */
	public function addPath( string $path ) : void
	{
		$this->searchPaths->add( $path );
	}

	/**
	 * Replaces the current search path array with a new one.
	 *
	 * @param array $paths
	 */
	public function setPaths( Vector<string> $paths ) : void
	{
		$this->searchPaths = $paths;
	}

	/**
	 * @return array
	 */
	public function getPaths() : Vector<string>
	{
		return $this->searchPaths;
	}

	/**
	 * @throws \Fastuc\View\Exception if the view was not found on any search path.
	 * @param string $name
	 * @return string
	 */
	public function find( string $name )
	{
		if( isset( $this->cachedPaths[ $name ] ) )
		{
			return $this->cachedPaths[ $name ];
		}

		foreach( $this->searchPaths as $path )
		{
			$fullPath = $path . DIRECTORY_SEPARATOR . $name . '.php';
			if( file_exists( $fullPath ) )
			{
				$this->cachedPaths[ $name ] = $fullPath;
				return $fullPath;
			}
		}

		throw new \Fastuc\View\Exception( "Template '$name' not found." );
	}
}

