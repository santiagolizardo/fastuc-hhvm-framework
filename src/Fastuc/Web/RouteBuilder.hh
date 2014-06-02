<?hh // strict
namespace Fastuc\Web;

class RouteBuilder
{
	private Route $route;

	public function __construct()
	{
		$this->route = new Route;
	}

	public function forController( string $controller ) : this
	{
		$this->route->setController( $controller );
		return $this;
	}

	public function withDomain( string $domain ) : this
	{
		$this->route->setDomainMatcher( $domain );
		return $this;
	}

	public function withPath( string $path ) : this
	{
		$this->route->setPathMatcher( $path );
		return $this;
	}

	public function withName( ?string $name ) : this
	{
		$this->route->setName( $name );
		return $this;
	}

	public function build()
	{
		return $this->route;
	}
}

