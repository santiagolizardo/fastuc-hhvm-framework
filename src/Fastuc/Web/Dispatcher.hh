<?hh // strict
namespace Fastuc\Web;

use \Fastuc\ClassLoader;

/**
 * This class loads a controller or another taking the current URL and other variables as reference.
 */
class Dispatcher
{
	/**
	 * @var ClassLoader
	 */
	private ClassLoader $classLoader;

	/**
	 * @var string
	 */
	private string $contextPath;

	/**
	 * @var string
	 */
	private string $baseControllerNs;

	/**
	 * @var string
	 */
	private string $baseControllerPath;

	/**
	 * @var array
	 */
	private Vector<Route> $routes;

	public function __construct( string $contextPath = '' )
	{
		$this->classLoader = ClassLoader::getInstance();

		$this->contextPath = $contextPath;
		$this->routes = new Vector<Route>;

		$this->baseControllerPath = $this->baseControllerNs = '';
	}

	/**
	 * @param string $baseControllerPath
	 */
	public function setBaseControllerPath( string $baseControllerPath ) : void
	{
		$this->baseControllerPath = $baseControllerPath;
	}

	/**
	 * @return string
	 */
	public function getBaseControllerPath() : string
	{
		return $this->baseControllerPath;
	}

	/**
	 * @param string $baseControllerNs
	 */
	public function setBaseControllerNs( string $baseControllerNs ) : void
	{
		$this->baseControllerNs = $baseControllerNs;
	}

	/**
	 * @return string
	 */
	public function getBaseControllerNs() : string
	{
		return $this->baseControllerNs;
	}

	/**
	 * @param string $contextPath
	 */
	public function setContextPath( string $contextPath ) : void
	{
		$this->contextPath = $contextPath;
	}

	public function setRoutes( Vector<Route> $routes ) : void
	{
		$this->routes = $routes;
	}

	public function getRoutes() : Vector<Route>
	{
		return $this->routes;
	}

	/**
	 * Launch the actual dispatching process.
	 */
	public function run() : void
	{
		if( !empty( $this->baseControllerPath ) )
		{
			$this->classLoader->addInclusionPath( $this->baseControllerPath );
		}

		$controllerRoute = $this->getControllerRoute();
		$route = $this->getControllerNameAndAttributes( $controllerRoute );

		if( null == $route )
		{
			$this->runController( 'errorPage', Map<string, mixed> { 0 => 500, 1 => 'Route not found' } );
			return;
		}

		try
		{
			$this->runController( $route->getController(), $route->getAttributes() );
		}
		catch( \Exception $e )
		{
			$this->runController( 'errorPage', Map<string, mixed> { 0 => 500, 1 => $e->getMessage() } );
		}
	}

	private function runController( string $controllerName, Map<string, mixed> $controllerAttributes ) : void
	{
		$controllerClassName = $this->getControllerClassName( $controllerName );
		if( class_exists( $controllerClassName ) )
		{
			$ctrlInstance = new $controllerClassName;
		}
		else
		{
			$ctrlInstance = new \Fastuc\Controller\Error;
		}

		$ctrlInstance->init();
		$ctrlInstance->setAttributes( $controllerAttributes );
			
		$methodName = $_SERVER['REQUEST_METHOD'];
		$ctrlInstance->beforeMethod( $methodName );
		$ctrlInstance->executeMethod( $methodName );
		$ctrlInstance->afterMethod( $methodName );
	}

	/**
	 * Returns the current request path, excluding context path, if any.
	 *
	 * @return string
	 */
	private function getControllerRoute() : string
	{
		$requestUri = $_SERVER['REQUEST_URI'];

		// Remove query string. Ex: /ostests/foo/bar?scott=tiger => /ostests/foo/bar
		$route = preg_replace( '/(\?.*)$/', '', $requestUri );

		// Remove context path. Ex: /ostests/foo/bar => /foo/bar
		$route = str_replace( $this->contextPath, '', $route );

		// Remove leading slash. Ex: /foo/bar => foo/bar
		$route = ltrim( $route, '/' ); 

		return $route;
	}

	private function getControllerNameAndAttributes( string $requestPath ) : Route
	{
		$webRouter = new \Fastuc\Web\Router( $this->routes );
		$route = $webRouter->find( $_SERVER['HTTP_HOST'], $requestPath );
		if( null !== $route )
		{
			$path = $this->getControllerPath( $route->getController() );
			if( false == file_exists( $path ) )
			{
				trigger_error( "Route '$route[pattern]' was defined but controller '$route[controller]' does not exist", E_USER_WARNING );

				$route->setController( 'errorPage' );
				$route->setAttributes( [ 500, $requestPath ] );
			}
		}
		else
		{
			$route = new Route;
			$path = $this->getControllerPath( $requestPath );
			if( true == file_exists( $path ) )
			{
				$route->setController( $requestPath );
				$route->setAttributes( [] );
			}
			else
			{
				$route->setController( 'errorPage' );
				$route->setAttributes( Map<string, mixed> { 0 => 404, 1=> "The request path '$requestPath' is not associated to a controller." } );
			}
		}

		return $route;
	}

	/**
	 * @param string $route
	 * @return string An absolute path to the controller file.
	 */
	private function getControllerPath( string $route ) : ?string
	{	
		$path = $this->baseControllerPath . $route . '.php';
		if( file_exists( $path ) )
		{
			return $path;
		}
		$path = $this->baseControllerPath . \Fastuc\Utils\Strings::capitalizeWords( $route ) . '.php';
		if( file_exists( $path ) )
		{
			return $path;
		}
		return null;
	}

	/**
	 * @param string $route
	 * @return string
	 */
	private function getControllerClassName( string $route ) : string
	{
		$webSeparator = '/';
		$components = explode( $webSeparator, $route );
		array_walk( $components, function( &$value, $index )
			{
				$value = ucfirst( $value );
			}
		);

		return $this->baseControllerNs . implode( '\\', $components );
	}
}

