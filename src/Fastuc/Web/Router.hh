<?hh // strict
namespace Fastuc\Web;

class Router
{
	/**
	 * @var array
	 */
	private Vector<Route> $routes;

	/**
	 * @param array $routes
	 */
	public function __construct( Vector<Route> $routes )
	{
		$this->routes = $routes;
	}

	/**
	 * @param string $name
	 * @return bool
	 */
	public function exists( string $name ) : bool
	{
		foreach( $this->routes as $route )
		{
			if( $route instanceof RouteBuilder ) $route = $route->build();
			if( $route->getName() === $name )
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * @param string $name
	 * @return string
	 */
	public function get( string $name ) : ?Route 
	{
		foreach( $this->routes as $route )
		{
			if( $route instanceof RouteBuilder ) $route = $route->build();
			if( $route->getName() != null && $route->getName() == $name )
				return $route;
		}
	}

	/**
	 * @param string $domain
	 * @param string $file
	 * @return array|null
	 */
	public function find( string $domain, mixed $file ) : ?Route
	{
		foreach( $this->routes as $route )
		{
			if( $route instanceof RouteBuilder )
			{
				$route = $route->build();
			}

			$attrs = new Map<string, mixed>;

			if( false == $this->matchesDomain( $domain, $route, $attrs ) )
			{
				continue;
			}

			if( false == $this->matchesFile( $file, $route, $attrs ) )
			{
				continue;
			}

			$route->setAttributes( $attrs );
			return $route;
		}

		return null;
	}

	private function matchesDomain( string $domain, Route $route, Map<string, mixed> &$attrs ) : bool
	{
		if( !isset( $route->getDomain() ) )
		{
			return true;
		}

		return $this->matches( $domain, $route->getDomain(), $attrs );
	}

	private function matchesFile( string $file, Route $route, Map<string, mixed> &$attrs ) : bool
	{
		if( !isset( $route->getPathMatcher() ) )
		{
			return true;
		}

		return $this->matches( $file, $route->getPathMatcher(), $attrs );
	}

	private function matches( string $subject, string $pattern, Map<string, mixed> &$attrs ) : bool
	{
		$reString = '#^' . preg_quote( $pattern, '#' ) . '$#';
		$reString = '#^' . $pattern . '$#';
		if( preg_match( $reString, $subject, $matches ) )
		{
			foreach( $matches as $k => $v )
			{
				$attrs->set( $k, $v );
			}
			return true;
		}

		return false;
	}
}

