<?hh // strict
namespace Fastuc\Web;

class Route
{
	public static function build( string $controller, string $name = null ) : RouteBuilder
	{
		$builder = new RouteBuilder;
		$builder->forController( $controller );
		$builder->withName( $name );
		return $builder;
	}

	private string $name;
	private string $pathMatcher;
	private string $controller;
	private string $domain;

	private Map<string, mixed> $attributes;

	public function __construct()
	{
		$this->name = null;
		$this->pathMatcher = null;
		$this->controller = null;
		$this->domain = null;

		$this->attributes = new Map<string, mixed>;
	}

	public function setName( ?string $name ) : void
	{
		$this->name = $name;
	}

	public function getName() : ?string
	{
		return $this->name;
	}

	public function setPathMatcher( ?string $pathMatcher ) : void
	{
		$this->pathMatcher = $pathMatcher;
		return $this;
	}

	public function getPathMatcher() : string
	{
		return $this->pathMatcher;
	}

	public function setController( string $controller ) : this
	{
		$this->controller = $controller;
		return $this;
	}

	public function getController() : string
	{
		return $this->controller;
	}

	public function setDomainMatcher( string $domain ) : this
	{
		$this->domain = $domain;
		return $this;
	}

	public function getDomain() : ?string
	{
		return $this->domain;
	}

	public function setAttributes( Map<string, mixed> $attributes ) : void
	{
		$this->attributes = $attributes;
	}

	public function getAttributes() : Map<string, mixed>
	{
		return $this->attributes;
	}
}

